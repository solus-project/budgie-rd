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

#pragma once

#include <QObject>

#include "wayland-window.h"

namespace Budgie::Compositor
{
    /**
     * Implement WlShell specific version of the WaylandWindow
     */
    class WaylandWindowWlShell : public WaylandWindow
    {
        Q_OBJECT

        friend class WaylandWindow;

    protected:
        explicit WaylandWindowWlShell(SurfaceItem *surface, QWaylandWlShellSurface *wl_shell);

    private:
        QWaylandWlShellSurface *m_shell;
    };
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
