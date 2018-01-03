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

    // Rebuild our input layers and such
    presentSurfaceItem(item);
    rebuildPresentables();

    // Time to redraw
    requestUpdate();
    return view;
}

/**
 * Push a item into the presentation layer
 */
void OpenGLDisplay::presentSurfaceItem(Compositor::SurfaceItem *item)
{
    std::lock_guard<std::mutex> lock(m_listLock);

    m_layers[item->layer()] << item;
}

/**
 * Remove the item from all presentation layers
 */
void OpenGLDisplay::unpresentSurfaceItem(Compositor::SurfaceItem *item)
{
    std::lock_guard<std::mutex> lock(m_listLock);

    // Remove from input + rendering
    m_renderables.removeAll(item);
    m_inputSurfaceItems.removeAll(item);
    m_layers[item->layer()].removeAll(item);
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

    unpresentSurfaceItem(item);

    qDebug() << "Unmapped: " << view.data();
    m_views.remove(item);

    // Time to redraw
    requestUpdate();
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

        auto item = view->item();
        auto surface = item->surface();

        // Rectangle for the whole texture size
        const QRect targetRect(QPoint(0, 0), item->size());

        // Position expected in our screen space
        const QRect positionRect(-item->position(), ourSize);
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
 * Return pointers to items that we have mapped and care about input.
 */
QList<Budgie::Compositor::SurfaceItem *> OpenGLDisplay::inputSurfaceItems()
{
    return m_inputSurfaceItems;
}

void OpenGLDisplay::rebuildPresentables()
{
    std::lock_guard<std::mutex> lock(m_listLock);

    QList<Budgie::Compositor::SurfaceItem *> drawables;
    QList<Budgie::Compositor::SurfaceItem *> input;

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

void OpenGLDisplay::moveSurfaceItemToIndex(Budgie::Compositor::SurfaceItem *item, int index)
{
    std::lock_guard<std::mutex> lock(m_listLock);

    // No sense doing this for a small list
    RenderLayer layer = item->layer();
    int size = m_layers[layer].size();

    if (size < 2) {
        return;
    }

    // Find out where we are
    int position = m_layers[layer].indexOf(item);
    if (position <= 0) {
        return;
    }

    if (index < 1) {
        index = size - 1;
    }

    m_layers[layer].move(position, index);
}
/**
 * Our implementation simply moves the item to the end of its current
 * rendering layer.
 */
void OpenGLDisplay::raiseSurfaceItem(Budgie::Compositor::SurfaceItem *item)
{
    moveSurfaceItemToIndex(item, -1);
    rebuildPresentables();
    requestUpdate();
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
