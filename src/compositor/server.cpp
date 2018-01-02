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
      m_xdg_shell_v5(new QWaylandXdgShellV5(this))
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
}

void Server::create()
{
    // Just pass it back up for now.
    QWaylandCompositor::create();

    // This is where we just fake the hell out of it for now.
    auto output = new QWaylandOutput();
    QWaylandOutputMode mode(QSize(1024, 768), 60000);
    output->addMode(mode);
    output->setCurrentMode(mode);

    // This is code we WOULD use, i.e. construct a display and store it.
    // We'll actually need to add sorting based on the index but in theory
    // we could swap to a map of index->display
    auto display = m_renderer->createDisplay(output);
    if (!display) {
        qWarning() << "Failed to construct a valid display for: " << output;
        QCoreApplication::quit();
        return;
    }

    auto window = display->window();
    if (window == nullptr) {
        qWarning() << "Broken Renderer is not returning the Window";
        QCoreApplication::quit();
        return;
    }

    output->setWindow(window);

    // Store the display now
    m_displays << QSharedPointer<Display>(display);
}

void Server::surfaceCreated(QWaylandSurface *surface)
{
    Q_UNUSED(surface);
}

void Server::surfaceDestroying(QWaylandSurface *surface)
{
    Q_UNUSED(surface);
}

void Server::wlShellCreated(QWaylandWlShellSurface *shell)
{
    Q_UNUSED(shell);
}

void Server::xdgShellv5Created(QWaylandXdgSurfaceV5 *shell)
{
    Q_UNUSED(shell);
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
