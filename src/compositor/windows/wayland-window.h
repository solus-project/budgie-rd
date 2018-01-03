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

#include <QWaylandWlShellSurface>
#include <QWaylandXdgSurfaceV5>

#include "compositor-common.h"
#include "surface-item.h"

namespace Budgie::Compositor
{
    /**
     * Wrap up a Wayland surface as a toplevel window object within our view
     * and input model. Effectively this maps a root surface (owned by the
     * compositor) and tracks other metadata such as title, etc.
     *
     * Any SurfaceItem within the compositor is automatically mapped to a given
     * output, the Window is used to provide a logical unit for presentation.
     * Any non window surface will not be rendered unless it is a child surface
     * of the windows root surface.
     */
    class WaylandWindow : public QObject
    {
        Q_OBJECT

        friend class Server;

    public:
        SurfaceItem *rootSurface();

    protected:
        /**
         * Construct a new WaylandWindow instance for the given WlShellSurface
         */
        static WaylandWindow *create(SurfaceItem *surface, QWaylandWlShellSurface *wl_shell);

        /**
         * Construct a new WaylandWindow instance for given XDG Shell Surface
         */
        static WaylandWindow *create(SurfaceItem *surface, QWaylandXdgSurfaceV5 *xdg_shell);

        /**
         * Construct a new SurfaceItem object for the given Wayland surface
         */
        explicit WaylandWindow(SurfaceItem *rootSurface);

    private:
        SurfaceItem *m_rootSurface;
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
