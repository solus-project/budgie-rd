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

#include <QHash>
#include <QObject>
#include <QSharedPointer>
#include <QWaylandCompositor>

/* Extensions */
#include <QWaylandSurface>
#include <QWaylandWlShell>
#include <QWaylandXdgShellV5>

#include "surface-item.h"
#include "window.h"

namespace Budgie
{
    /**
     * The Budgie::Compositor handles the lifecycle for the main compositor
     * process, and will load the relevant implementation to handle actually
     * rendering.
     */
    class Compositor : public QObject
    {
        Q_OBJECT

    public:
        explicit Compositor();

        /**
         * Request that the compositor now run, i.e. create the server.
         */
        void run();

    private slots:
        void onCreated();

        void surfaceCreated(QWaylandSurface *surface);
        void wlShellSurfaceCreated(QWaylandWlShellSurface *surface);
        void xdgSurfaceCreated(QWaylandXdgSurfaceV5 *surface);

        void surfaceDestroyed();

    private:
        QSharedPointer<QWaylandCompositor> m_compositor;

        /* Dummy window. Shush. */
        QSharedPointer<CompositorWindow> m_window;

        /* Our Wayland extensions */
        QScopedPointer<QWaylandWlShell> m_wl_shell;
        QScopedPointer<QWaylandXdgShellV5> m_xdg_shell_v5;

        /* TODO: Add v6 xdg shell when we have Qt 5.10
        QScopedPointer<QWaylandXdgShellV6> m_xdg_shell_v6;
        */

        /* Map QWaylandSurface into our own items */
        QHash<QWaylandSurface *, QSharedPointer<CompositorSurfaceItem>> m_surfaces;

        CompositorSurfaceItem *getSurfaceItem(QWaylandSurface *surface);

        /* Map a list to each layer */
        QHash<RenderLayer, QList<CompositorSurfaceItem *>> m_renderables;

        void renderLayer(RenderLayer layer);
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
