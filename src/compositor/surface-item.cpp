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

#include "surface-item.h"

Budgie::CompositorSurfaceItem::CompositorSurfaceItem(QWaylandSurface *surface) : m_surface(surface)
{
    m_compositor = m_surface->compositor();
}

QWaylandSurface *Budgie::CompositorSurfaceItem::surface()
{
    return m_surface;
}

QWaylandCompositor *Budgie::CompositorSurfaceItem::compositor()
{
    return m_compositor;
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
