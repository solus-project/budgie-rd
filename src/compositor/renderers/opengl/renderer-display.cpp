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
#include "window.h"

using namespace Budgie::Compositor;

OpenGLDisplay::OpenGLDisplay(Compositor::ServerInterface *server, QWaylandOutput *output)
    : Display(output, this), m_server(server)
{
    connect(output, &QWaylandOutput::currentModeChanged, this, &OpenGLDisplay::currentModeChanged);
}

OpenGLDisplay::~OpenGLDisplay()
{
    // Destroy our resources on current GL context
    makeCurrent();
    m_blitter.destroy();
}

/**
 * A new window is being added to our display, so we'll need to create a view
 * capable of rendering it.
 */
QWaylandView *OpenGLDisplay::mapWindow(Compositor::Window *window)
{
    std::lock_guard<std::mutex> lock(m_viewLock);

    if (m_views.contains(window)) {
        qDebug() << "Accounting error: Already know about " << window;
        return nullptr;
    }
    auto view = new OpenGLView(this, window);
    m_views.insert(window, QSharedPointer<OpenGLView>(view));
    qDebug() << "Mapped:" << view;

    // Rebuild our input layers and such
    presentWindow(window);
    rebuildPresentables();

    // Time to redraw
    requestUpdate();
    return view;
}

/**
 * Push a window into the presentation layer
 */
void OpenGLDisplay::presentWindow(Compositor::Window *window)
{
    std::lock_guard<std::mutex> lock(m_listLock);

    m_layers[window->layer()] << window;
}

/**
 * Remove the window from all presentation layers
 */
void OpenGLDisplay::unpresentWindow(Compositor::Window *window)
{
    std::lock_guard<std::mutex> lock(m_listLock);

    // Remove from input + rendering
    m_renderables.removeAll(window);
    m_inputWindows.removeAll(window);
    m_layers[window->layer()].removeAll(window);
}

/**
 * A window has been removed from our display, so we need to remove the corresponding
 * View for it.
 */
void OpenGLDisplay::unmapWindow(Compositor::Window *window)
{
    std::lock_guard<std::mutex> lock(m_viewLock);

    auto view = m_views.value(window, nullptr);
    if (!view) {
        qDebug() << "Accounting error, unknown window: " << window;
        return;
    }

    unpresentWindow(window);

    qDebug() << "Unmapped: " << view.data();
    m_views.remove(window);

    // Time to redraw
    requestUpdate();
}

/**
 * Grab the appropriate view for the given window.
 *
 * This is used by the compositor to find the display specific output for
 * any surface.
 */
QWaylandView *OpenGLDisplay::view(Compositor::Window *window)
{
    auto view = m_views.value(window, nullptr);
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
    requestUpdate();
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

    auto bindID = GL_TEXTURE_2D;
    auto ourSize = size();

    // Render all textures here now.
    for (auto renderable : m_renderables) {
        auto view = m_views.value(renderable, nullptr);
        if (!view) {
            continue;
        }
        auto texture = view->texture();
        if (!texture) {
            continue;
        }
        auto origin = view->textureOrigin();
        if (texture->format() != bindID) {
            m_blitter.bind(bindID);
        }

        auto window = view->window();
        auto surface = window->surface();

        // Rectangle for the whole texture size
        const QRect targetRect(QPoint(0, 0), window->size());

        // Position expected in our screen space
        const QRect positionRect(-window->position(), ourSize);
        const QMatrix4x4 target = QOpenGLTextureBlitter::targetTransform(targetRect, positionRect);

        // Draw the texture
        surface->frameStarted();
        m_blitter.blit(texture->textureId(), target, origin);
        surface->sendFrameCallbacks();
    }

    funcs->glDisable(GL_BLEND);

    m_blitter.release();
}

/*
 * Hook up window functions so that we emit signals for the compositor to
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
QList<Budgie::Compositor::Window *> OpenGLDisplay::inputWindows()
{
    return m_inputWindows;
}

void OpenGLDisplay::rebuildPresentables()
{
    std::lock_guard<std::mutex> lock(m_listLock);

    QList<Budgie::Compositor::Window *> drawables;
    QList<Budgie::Compositor::Window *> input;

    static int minLayer = static_cast<int>(Compositor::MinLayer);
    static int maxLayer = static_cast<int>(Compositor::MaxLayer);

    // Render layer is back to front along z-index + layer
    for (int i = minLayer; i < maxLayer; i++) {
        RenderLayer layer = static_cast<RenderLayer>(i);

        for (auto window : m_layers[layer]) {
            drawables << window;
        }
    }

    // Input matching is front to back
    for (auto it = drawables.rbegin(); it != drawables.rend(); ++it) {
        // TODO: Check if this is an input candidate!
        input << *it;
    }

    m_renderables = drawables;
    m_inputWindows = input;
}

void OpenGLDisplay::moveWindowToIndex(Budgie::Compositor::Window *window, int index)
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
    if (position <= 0) {
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
void OpenGLDisplay::raiseWindow(Budgie::Compositor::Window *window)
{
    moveWindowToIndex(window, -1);
    rebuildPresentables();
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
