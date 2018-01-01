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

#include <QOpenGLTexture>
#include <QWaylandView>

#include "compositor-common.h"
#include "surface-item.h"

namespace Budgie
{
    /**
     * The CompositorView is used to map a CompositorSurfaceItem to an existing
     * CompositorWindow.
     *
     * In QtWayland terms this object has a reference to a QWaylandSurface and
     * inherits QWaylandView to map the surface to our QWaylandOutput, which in
     * our case is managed by the CompositorWindow.
     */
    class CompositorView : public QWaylandView
    {
        Q_OBJECT

    public:
        explicit CompositorView(CompositorWindow *window, CompositorSurfaceItem *surface);

        QOpenGLTexture *texture();

    private:
        CompositorWindow *m_window;
        CompositorSurfaceItem *m_surface;

        QOpenGLTexture *m_texture;
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
