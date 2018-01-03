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
#include "window-interface.h"

namespace Budgie::Compositor
{
    /**
     * Each display is a Wayland specific display implementation of the
     * DisplayInterface, and needs further extending by the primary
     * Renderer.
     */
    class Window : public QObject, public WindowInterface
    {
        Q_OBJECT

        friend class Server;

    protected:
        /**
         * Construct a new Window object for the given Wayland surface
         */
        Window(QWaylandSurface *surface);

    public:
        /**
         * Return the QWaylandSurface we're associated with
         */
        QWaylandSurface *surface();

        /**
         * Return the render layer we've been assigned
         */
        RenderLayer layer();

        QPoint position() override;
        QRect geometry() override;
        QSize size() override;

    protected:
        /**
         * Used by the server to assign our new layer
         */
        void setLayer(RenderLayer layer);

    private slots:
        void sizeChanged();

    private:
        QWaylandSurface *m_surface;
        QPoint m_position;
        QSize m_size;
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
