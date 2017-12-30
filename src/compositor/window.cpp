/*
 * This file is part of budgie-rd
 *
 * Copyright © 2017 Budgie Desktop Developers
 *
 * budgie-rd is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#include <QWaylandOutputMode>

#include "window.h"

Budgie::CompositorWindow::CompositorWindow(QWaylandOutput *output) : m_output(output)
{
    m_compositor = m_output->compositor();

    setSurfaceType(QWindow::OpenGLSurface);

    // Stupid but we're forced into demoMode right now
    setTitle("Nested RD Compositor");

    // Make sure we know about mode changes
    connect(m_output.data(),
            &QWaylandOutput::currentModeChanged,
            this,
            &Budgie::CompositorWindow::currentModeChanged);
    m_output->setWindow(this);
}

QWaylandOutput *Budgie::CompositorWindow::output()
{
    return m_output.data();
}

QWaylandCompositor *Budgie::CompositorWindow::compositor()
{
    return m_compositor;
}

void Budgie::CompositorWindow::currentModeChanged()
{
    auto mode = m_output->currentMode();
    auto size = mode.size();
    qDebug() << "currentModeChanged(): " << size;
    resize(size.width(), size.height());
    setPosition(m_output->position());
}

bool Budgie::CompositorWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        blitScreen();
        return true;
    default:
        return QWindow::event(event);
    }
}

void Budgie::CompositorWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (!isExposed()) {
        return;
    }

    blitScreen();
}

/**
 * We need to be redrawn
 */
void Budgie::CompositorWindow::scheduleDraw()
{
    requestUpdate();
}

/**
 * Quick helper to ensure we have OpenGL properly initialised
 */
void Budgie::CompositorWindow::ensureGL()
{
    if (m_GLContext) {
        m_GLContext->makeCurrent(this);
        return;
    }

    m_GLContext = new QOpenGLContext(this);
    m_GLContext->setFormat(requestedFormat());
    m_GLContext->create();
    m_GLContext->makeCurrent(this);

    initializeOpenGLFunctions();
}

/**
 * Anything requiring rendering will now be pushed to the screen
 */
void Budgie::CompositorWindow::blitScreen()
{
    // Make sure we have GL
    ensureGL();

    m_output->frameStarted();
    doRender();
    m_output->sendFrameCallbacks();

    // Spit out to the screen
    m_GLContext->swapBuffers(this);
}

/**
 * Perform any required rendering
 */
void Budgie::CompositorWindow::doRender()
{
    auto funcs = m_GLContext->functions();
    funcs->glClearColor(0.3f, 0.5f, 0.8f, 1.0f);
    funcs->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
