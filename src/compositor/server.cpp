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

#include "server.h"

using namespace Budgie::Compositor;

Server::Server()
    : m_wl_shell(new QWaylandWlShell(this)), m_xdg_shell_v5(new QWaylandXdgShellV5(this))
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
