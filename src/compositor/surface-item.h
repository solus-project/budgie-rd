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
#include <QWaylandSurface>

#include "compositor-common.h"

namespace Budgie::Compositor
{
    /**
     * Wrap each QWaylandSurface into a tree structure for rendering and
     * input matching.
     *
     * A SurfaceItem may have child nodes which are always subsurfaces.
     */
    class SurfaceItem : public QObject
    {
        Q_OBJECT

        friend class Server;

    protected:
        /**
         * Construct a new SurfaceItem object for the given Wayland surface
         */
        SurfaceItem(QWaylandSurface *surface);

    public:
        /**
         * Return the QWaylandSurface we're associated with
         */
        QWaylandSurface *surface();

        /**
         * Return the render layer we've been assigned
         */
        RenderLayer layer();

        /**
         * Are we actually renderable?
         */
        bool renderable();

        /**
         * Are we a cursor?
         */
        bool cursor();

        QPoint position();
        QRect geometry();
        QSize size();

    signals:

        /*
         * Emitted so the compositor can finally get us drawn on screen, after
         * our initial allocation of views.
         */
        void roleConfirmed();

    protected:
        /**
         * Used by the server to assign our new layer
         */
        void setLayer(RenderLayer layer);

        /**
         * Add the SurfaceItem as a known child of ours
         */
        void addChild(SurfaceItem *child);

        /**
         * Remove the SurfaceItem from the list of known children.
         */
        void removeChild(SurfaceItem *child);

        /**
         * Return the parent (if we have one)
         */
        SurfaceItem *parentItem();

    private slots:
        void sizeChanged();
        void hasContentChanged();

    private:
        QWaylandSurface *m_surface;
        QPoint m_position;
        QSize m_size;
        RenderLayer m_layer;
        bool m_roleConfirmed;
        bool m_renderable;

        QList<SurfaceItem *> m_children;
        SurfaceItem *m_parentItem;
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
