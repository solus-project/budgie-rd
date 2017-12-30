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

#pragma once

#include <QObject>
#include <QWaylandCompositor>
#include <QWaylandSurface>
#include <QWaylandWlShellSurface>
#include <QWaylandXdgSurfaceV5>

#include "compositor-common.h"

namespace Budgie
{
    /**
     * The CompositorSurfaceItem wraps a QWaylandSurface to provide general
     * abstraction so that it is in some way *usable* to the Budgie::Compositor.
     * This will provide all relevant properties and mapping so that it can
     * be rendered on screen.
     */
    class CompositorSurfaceItem : public QObject
    {
        Q_OBJECT

        friend class Compositor;

    public:
        explicit CompositorSurfaceItem(QWaylandSurface *surface);

        QWaylandSurface *surface();
        QWaylandCompositor *compositor();

        const QString &title();
        bool renderable();

        RenderLayer layer();

    protected:
        void setShellSurface(QWaylandWlShellSurface *surface);
        void setXdgSurfacev5(QWaylandXdgSurfaceV5 *surface);

    private:
        QWaylandSurface *m_surface;
        QWaylandCompositor *m_compositor;

        QWaylandWlShellSurface *m_shell_surface;
        QWaylandXdgSurfaceV5 *m_xdg_surface_v5;

        QString m_windowTitle;
        bool m_renderable;

        RenderLayer m_layer;
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
