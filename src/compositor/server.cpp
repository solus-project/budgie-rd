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

#include <QCoreApplication>

#include "compositor-renderer-interface.h"
#include "display.h"
#include "server.h"

using namespace Budgie::Compositor;

Server::Server(RendererInterface *renderer)
    : m_renderer(renderer), m_wl_shell(new QWaylandWlShell(this)),
      m_xdg_shell_v5(new QWaylandXdgShellV5(this)), m_seat(nullptr)
{
    // Hook up basic compositor signals so we know whats going on when we ::create()
    connect(this, &QWaylandCompositor::surfaceCreated, this, &Server::surfaceCreated);
    connect(this, &QWaylandCompositor::surfaceAboutToBeDestroyed, this, &Server::surfaceDestroying);

    // Now hook up each protocol
    connect(m_wl_shell, &QWaylandWlShell::wlShellSurfaceCreated, this, &Server::wlShellCreated);
    connect(m_xdg_shell_v5,
            &QWaylandXdgShellV5::xdgSurfaceCreated,
            this,
            &Server::xdgShellv5Created);

    connect(this, &QWaylandCompositor::defaultSeatChanged, this, &Server::wlSeatChanged);
    connect(this, &QWaylandCompositor::createdChanged, this, &Server::wlCreated);

    // Pass ourselves as an InputInterface to the renderer
    m_renderer->init(this);
}

bool Server::start()
{
    // Ask that we get created.
    create();

    // This is where we just fake the hell out of it for now.
    auto output = new QWaylandOutput(this, nullptr);
    QWaylandOutputMode mode(QSize(1024, 768), 60000);
    output->setPosition(QPoint(0, 0));
    output->addMode(mode, true);

    // This is code we WOULD use, i.e. construct a display and store it.
    // We'll actually need to add sorting based on the index but in theory
    // we could swap to a map of index->display
    auto display = m_renderer->createDisplay(output);
    if (!display) {
        qWarning() << "Failed to construct a valid display for: " << output;
        return false;
    }

    auto window = display->window();
    if (window == nullptr) {
        qWarning() << "Broken Renderer is not returning the Window";
        return false;
    }

    // Force connection and mode change now
    output->setWindow(window);
    output->setCurrentMode(mode);

    // Store the display now
    m_displays << QSharedPointer<Display>(display);

    // Get it on screen
    window->show();
    return true;
}

void Server::surfaceCreated(QWaylandSurface *surface)
{
    if (m_surfaces.contains(surface)) {
        qWarning() << "Accounting error: Already know about " << surface;
        return;
    }

    auto window = new Compositor::Window(surface);
    qDebug() << "Added surface:" << window;

    // TODO: Decide which output we wanna put this guy on and map it there.
    m_surfaces.insert(surface, QSharedPointer<Compositor::Window>(window));

    // Le Hacky Demos
    auto view = m_displays[0]->mapWindow(window);
    if (!view) {
        return;
    }
    view->setOutput(m_displays[0]->output());
    view->setPrimary();
}

/**
 * The WaylandSurface is about to be destroyed, so we must remove knowledge
 * of this from ourselves and all displays
 */
void Server::surfaceDestroying(QWaylandSurface *surface)
{
    auto window = m_surfaces.value(surface, nullptr);
    if (!window) {
        qWarning() << "Accounting error: Don't know about " << surface;
        return;
    }

    // Remove window from all displays
    for (auto &display : m_displays) {
        // TODO: If the display contains then unmap
        display->unmapWindow(window.data());
    }

    qDebug() << "Removed surface:" << window.data();

    m_surfaces.remove(surface);
}

void Server::wlShellCreated(QWaylandWlShellSurface *shell)
{
    Q_UNUSED(shell);
}

void Server::xdgShellv5Created(QWaylandXdgSurfaceV5 *shell)
{
    Q_UNUSED(shell);
}

/**
 * We've been created so we need to get ready to show stuff on screen.
 */
void Server::wlCreated()
{
    if (!isCreated()) {
        return;
    }
    // Enforce some kind of seat knowledge.
    wlSeatChanged(defaultSeat(), nullptr);
}

/**
 * Handle seat changes. In future we'll need to rebind active focus and such
 * and remove knowledge of the old seat from existing clients. For now, just
 * stash the pointer.
 */
void Server::wlSeatChanged(QWaylandSeat *newSeat, QWaylandSeat *oldSeat)
{
    Q_UNUSED(oldSeat);
    qDebug() << "Seat set to: " << newSeat;
    m_seat = newSeat;
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
