/*
 * This file is part of budgie-rd
 *
 * Copyright © 2017-2018 Budgie Desktop Developers
 *
 * budgie-rd is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#include <QDebug>
#include <QList>
#include <QOpenGLFunctions>

#include "renderer-display.h"
#include "surface-item.h"

using namespace Budgie::Compositor;

OpenGLDisplay::OpenGLDisplay(Compositor::ServerInterface *server, QWaylandOutput *output,
                             uint index)
    : QOpenGLWindow(QOpenGLWindow::PartialUpdateBlit), Display(output, this, index),
      m_server(server)
{
    connect(output, &QWaylandOutput::currentModeChanged, this, &OpenGLDisplay::currentModeChanged);

    // Qt OpenGL on Linux has vsync issues. If we set the primary display as synced
    // then the next displays will operate at the correct rate. However we will need
    // to test this in future with multiple native displays and different refresh
    // rates to verify the impact.
    QSurfaceFormat format;
    if (index == 0) {
        format.setSwapInterval(1);
    } else {
        format.setSwapInterval(0);
    }

    // We want double buffering.
    format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);

    setFormat(format);
}

OpenGLDisplay::~OpenGLDisplay()
{
    // Destroy our resources on current GL context
    makeCurrent();
    m_blitter.destroy();
}

/**
 * A new item is being added to our display, so we'll need to create a view
 * capable of rendering it.
 */
QWaylandView *OpenGLDisplay::mapSurfaceItem(Compositor::SurfaceItem *item)
{
    std::lock_guard<std::mutex> lock(m_viewLock);

    if (m_views.contains(item)) {
        qDebug() << "Accounting error: Already know about " << item;
        return nullptr;
    }
    auto view = new OpenGLView(this, item);
    m_views.insert(item, QSharedPointer<OpenGLView>(view));
    qDebug() << "Mapped:" << view;

    // Time to redraw
    refreshScreen();
    return view;
}

/**
 * Push a item into the presentation layer
 */
void OpenGLDisplay::mapWindow(WaylandWindow *window)
{
    {
        std::lock_guard<std::mutex> lock(m_listLock);
        m_layers[window->layer()] << window;
    }

    // We have a new window, when it updates, update us
    connect(window, &WaylandWindow::animationTick, this, &OpenGLDisplay::refreshScreen);

    // Rebuild our input layers and such
    rebuildPresentables();

    // Now redraw.
    refreshScreen();
}

/**
 * Remove the window from all presentation layers.
 */
void OpenGLDisplay::unmapWindow(WaylandWindow *window)
{
    std::lock_guard<std::mutex> lock(m_listLock);

    disconnect(window, &WaylandWindow::animationTick, this, &OpenGLDisplay::refreshScreen);

    // Remove from input + rendering
    m_renderables.removeAll(window);
    m_inputSurfaceItems.removeAll(window);
    m_layers[window->layer()].removeAll(window);
}

/**
 * A item has been removed from our display, so we need to remove the corresponding
 * View for it.
 */
void OpenGLDisplay::unmapSurfaceItem(Compositor::SurfaceItem *item)
{
    std::lock_guard<std::mutex> lock(m_viewLock);

    auto view = m_views.value(item, nullptr);
    if (!view) {
        qDebug() << "Accounting error, unknown item: " << item;
        return;
    }

    qDebug() << "Unmapped: " << view.data();
    m_views.remove(item);

    // Time to redraw
    refreshScreen();
}

/**
 * Grab the appropriate view for the given item.
 *
 * This is used by the compositor to find the display specific output for
 * any surface.
 */
QWaylandView *OpenGLDisplay::view(Compositor::SurfaceItem *item)
{
    auto view = m_views.value(item, nullptr);
    if (!view) {
        return nullptr;
    }
    return view.data();
}

void OpenGLDisplay::currentModeChanged()
{
    auto mode = output()->currentMode();
    auto geom = mode.size();
    resize(geom.width(), geom.height());
    setPosition(output()->position());
    qDebug() << "New mode:" << geom;

    // Redraw.
    refreshScreen();
}

/**
 * TODO: Grab any thing we're going to need later, such as the texture blitter.
 */
void OpenGLDisplay::initializeGL()
{
    qDebug() << "OpenGL initialized";
    m_blitter.create();
}

/**
 * Set the ticks and do main draw loop
 */
void OpenGLDisplay::paintGL()
{
    auto wl_output = output();
    wl_output->frameStarted();
    render();
    wl_output->sendFrameCallbacks();
}

/**
 * For each window, we'll foreach the surfaces in their natural order according
 * to the WaylandWindow. Here we'll just blit that to the display and apply any
 * transforms relative to the rootWindow.
 */
void OpenGLDisplay::renderSurface(WaylandWindow *rootWindow, SurfaceItem *item)
{
    // TODO: Render surface coordinate relative to window coordinate
    Q_UNUSED(rootWindow);

    auto view = m_views.value(item, nullptr);
    if (!view) {
        return;
    }
    auto texture = view->texture();
    if (!texture) {
        return;
    }
    auto origin = view->textureOrigin();

    auto bindID = GL_TEXTURE_2D;
    auto ourSize = size();

    if (texture->format() != bindID) {
        m_blitter.bind(bindID);
    }

    auto surface = item->surface();

    // Rectangle for the whole texture size
    const QRect targetRect(QPoint(0, 0), item->size());

    // Position expected in our screen space
    QPoint position = rootWindow->position() + item->position();
    const QRect positionRect(-position, ourSize);
    QMatrix4x4 target = QOpenGLTextureBlitter::targetTransform(targetRect, positionRect);
    auto scale = rootWindow->scale();
    target.scale(scale.x(), scale.y());

    // Draw the texture
    surface->frameStarted();
    m_blitter.setOpacity(float(rootWindow->opacity()));
    m_blitter.blit(texture->textureId(), target, origin);
    surface->sendFrameCallbacks();
}

/**
 * Our main render routine
 *
 * TODO: Suck less. Considerably.
 */
void OpenGLDisplay::render()
{
    auto funcs = context()->functions();
    funcs->glClearColor(0.3f, 0.5f, 0.8f, 1.0f);
    funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_blitter.bind();

    // Enable alpha composite
    funcs->glEnable(GL_BLEND);
    funcs->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Pass all of our window surfaces off to the main render function
    for (auto renderable : m_renderables) {
        renderable->surfaceForeach(this, (SurfaceFunctor)&OpenGLDisplay::renderSurface);
    }

    funcs->glDisable(GL_BLEND);

    m_blitter.release();
}

/*
 * Hook up item functions so that we emit signals for the compositor to
 * hook up, this way we centralise the real input management within the
 * compositor and not the renderers.
 */

void OpenGLDisplay::mouseMoveEvent(QMouseEvent *e)
{
    m_server->dispatchMouseEvent(this, e);
}

void OpenGLDisplay::mousePressEvent(QMouseEvent *e)
{
    m_server->dispatchMouseEvent(this, e);
}

void OpenGLDisplay::mouseReleaseEvent(QMouseEvent *e)
{
    m_server->dispatchMouseEvent(this, e);
}

void OpenGLDisplay::keyPressEvent(QKeyEvent *e)
{
    m_server->dispatchKeyEvent(this, e);
}

void OpenGLDisplay::keyReleaseEvent(QKeyEvent *e)
{
    m_server->dispatchKeyEvent(this, e);
}

void OpenGLDisplay::touchEvent(QTouchEvent *e)
{
    m_server->dispatchTouchEvent(this, e);
}

void OpenGLDisplay::wheelEvent(QWheelEvent *e)
{
    m_server->dispatchWheelEvent(this, e);
}

/**
 * Return pointers to windows that we have mapped and care about input.
 */
QList<WaylandWindow *> OpenGLDisplay::inputWindows()
{
    return m_inputSurfaceItems;
}

void OpenGLDisplay::rebuildPresentables()
{
    std::lock_guard<std::mutex> lock(m_listLock);

    QList<WaylandWindow *> drawables;
    QList<WaylandWindow *> input;

    static int minLayer = static_cast<int>(Compositor::MinLayer);
    static int maxLayer = static_cast<int>(Compositor::MaxLayer);

    // Render layer is back to front along z-index + layer
    for (int i = minLayer; i < maxLayer; i++) {
        RenderLayer layer = static_cast<RenderLayer>(i);

        for (auto item : m_layers[layer]) {
            drawables << item;
        }
    }

    // Input matching is front to back
    for (auto it = drawables.rbegin(); it != drawables.rend(); ++it) {
        // TODO: Check if this is an input candidate!
        input << *it;
    }

    m_renderables = drawables;
    m_inputSurfaceItems = input;
}

void OpenGLDisplay::moveWindowToIndex(WaylandWindow *window, int index)
{
    std::lock_guard<std::mutex> lock(m_listLock);

    // No sense doing this for a small list
    RenderLayer layer = window->layer();
    int size = m_layers[layer].size();

    if (size < 2) {
        return;
    }

    // Find out where we are
    int position = m_layers[layer].indexOf(window);
    if (position < 0) {
        return;
    }

    if (index < 1) {
        index = size - 1;
    }

    m_layers[layer].move(position, index);
}
/**
 * Our implementation simply moves the window to the end of its current
 * rendering layer.
 */
void OpenGLDisplay::raiseWindow(WaylandWindow *window)
{
    moveWindowToIndex(window, -1);
    rebuildPresentables();
    refreshScreen();
}

/**
 * Slot provided to just do a redraw.
 */
void OpenGLDisplay::refreshScreen()
{
    update();
}

/**
 * We've been instructed by the compositor to adjust our displayed cursor
 * surface.
 */
void OpenGLDisplay::setCursorSurface(SurfaceItem *surface, int hotX, int hotY)
{
    qDebug() << "Surface set to : " << surface;
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=4 tabstop=4 expandtab:
 * :indentSize=4:tabSize=4:noTabs=true:
 */
