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

#include "compositor.h"
#include "view.h"
#include "window.h"

Budgie::CompositorWindow::CompositorWindow(Budgie::Compositor *compositor, QWaylandOutput *output)
    : m_compositor(compositor), m_output(output)
{
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
    return m_compositor->compositor();
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

    m_GLBlitter.create();
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

    m_GLBlitter.bind();

    // Blit all relevant textures now
    for (auto surface : m_compositor->getRenderables(this)) {
        renderSurface(surface);
    }

    m_GLBlitter.release();
}

void Budgie::CompositorWindow::renderSurface(Budgie::CompositorSurfaceItem *item)
{
    // TODO: Add some kind of checking to make sure we're the right view for the item!
    Q_UNUSED(item);
}

/**
 * We've been asked to map this surface onto our display
 */
Budgie::CompositorView *Budgie::CompositorWindow::mapSurface(Budgie::CompositorSurfaceItem *surface)
{
    if (m_views.contains(surface)) {
        qDebug() << "Accounting error, we already have: " << surface;
        return nullptr;
    }
    auto view = new Budgie::CompositorView(this, surface);
    m_views.insert(surface, QSharedPointer<Budgie::CompositorView>(view));
    return view;
}

void Budgie::CompositorWindow::unmapSurface(Budgie::CompositorSurfaceItem *surface)
{
    if (!m_views.contains(surface)) {
        qDebug() << "Unknown surface: " << surface;
        return;
    }
    m_views.remove(surface);
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
