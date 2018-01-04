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
#include "window-interface.h"

namespace Budgie::Compositor
{
    class WaylandWindow;

    typedef void (QObject::*SurfaceFunctor)(WaylandWindow *rootWindow, SurfaceItem *item);

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
    class WaylandWindow : public QObject, public WindowInterface
    {
        Q_OBJECT
        Q_PROPERTY(double opacity READ opacity WRITE setOpacity NOTIFY opacityChanged)

        friend class Server;

    public:
        SurfaceItem *rootSurface();

        /* Override some basic WindowInterface APIs */
        QPoint position() override;
        QRect geometry() override;
        QSize size() override;

        /**
         * Return the currently set window opacity.
         */
        double opacity();

        /**
         * Return the current rendering layer for this window.
         */
        RenderLayer layer();

        /**
         * Call the following function with the correct rendering order
         */
        void surfaceForeach(QObject *instance, SurfaceFunctor f);

    signals:

        void opacityChanged();

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

        /**
         * Set the rendering layer for this window.
         */
        void setLayer(RenderLayer layer);

        /**
         * Set the new position for this window
         */
        void setPosition(QPoint position);

        /**
         * Update the opacity
         */
        void setOpacity(double opacity);

    private:
        SurfaceItem *m_rootSurface;
        RenderLayer m_layer;
        QPoint m_position;
        double m_opacity;
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
