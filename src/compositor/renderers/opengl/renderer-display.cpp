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
#include <QOpenGLFunctions>

#include "renderer-display.h"

using namespace Budgie::Compositor;

OpenGLDisplay::OpenGLDisplay(Compositor::InputInterface *input, QWaylandOutput *output)
    : Display(output, this), m_input(input)
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
    if (m_views.contains(window)) {
        qDebug() << "Accounting error: Already know about " << window;
        return nullptr;
    }
    auto view = new OpenGLView(this, window);
    m_views.insert(window, QSharedPointer<OpenGLView>(view));
    qDebug() << "Mapped:" << view;

    // Time to redraw
    requestUpdate();
    return view;
}

/**
 * A window has been removed from our display, so we need to remove the corresponding
 * View for it.
 */
void OpenGLDisplay::unmapWindow(Compositor::Window *window)
{
    auto view = m_views.value(window, nullptr);
    if (!view) {
        qDebug() << "Accounting error, unknown window: " << window;
        return;
    }
    qDebug() << "Unmapped: " << view.data();
    m_views.remove(window);

    // Time to redraw
    requestUpdate();
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

    // TODO: Render all textures here now.
    for (auto view : m_views) {
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
    m_input->dispatchMouseEvent(this, e);
}

void OpenGLDisplay::mousePressEvent(QMouseEvent *e)
{
    m_input->dispatchMouseEvent(this, e);
}

void OpenGLDisplay::mouseReleaseEvent(QMouseEvent *e)
{
    m_input->dispatchMouseEvent(this, e);
}

void OpenGLDisplay::keyPressEvent(QKeyEvent *e)
{
    m_input->dispatchKeyEvent(this, e);
}

void OpenGLDisplay::keyReleaseEvent(QKeyEvent *e)
{
    m_input->dispatchKeyEvent(this, e);
}

void OpenGLDisplay::touchEvent(QTouchEvent *e)
{
    m_input->dispatchTouchEvent(this, e);
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
