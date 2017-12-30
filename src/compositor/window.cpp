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
    if (mGLContext) {
        mGLContext->makeCurrent(this);
        return;
    }

    mGLContext = new QOpenGLContext(this);
    mGLContext->setFormat(requestedFormat());
    mGLContext->create();
    mGLContext->makeCurrent(this);

    initializeOpenGLFunctions();
}

/**
 * Anything requiring rendering will now be pushed to the screen
 */
void Budgie::CompositorWindow::blitScreen()
{
    // Make sure we have GL
    ensureGL();

    /* TODO: Render here */

    // Spit out to the screen
    mGLContext->swapBuffers(this);
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
