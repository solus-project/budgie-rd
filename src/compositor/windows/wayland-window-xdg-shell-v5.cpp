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

#include "wayland-window-xdg-shell-v5.h"

using namespace Budgie::Compositor;

WaylandWindowXdgShellV5::WaylandWindowXdgShellV5(SurfaceItem *surface, QWaylandXdgSurfaceV5 *wl_xdg)
    : WaylandWindow(surface), m_xdg(wl_xdg)
{
    // TODO: Hook up connections to the root surface
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
