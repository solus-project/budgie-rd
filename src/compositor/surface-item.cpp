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

Budgie::CompositorSurfaceItem::CompositorSurfaceItem(QWaylandSurface *surface)
    : m_surface(surface), m_shell_surface(nullptr), m_xdg_surface_v5(nullptr), m_renderable(false),
      m_layer(RenderLayer::APPLICATION)
{
    m_compositor = m_surface->compositor();
}

/**
 * Get the QWaylandSurface we're associated with
 */
QWaylandSurface *Budgie::CompositorSurfaceItem::surface()
{
    return m_surface;
}

/**
 * Get the QWaylandCompositor we're associated with
 */
QWaylandCompositor *Budgie::CompositorSurfaceItem::compositor()
{
    return m_compositor;
}

/**
 * Typically only shell/xdg items will be rendered
 */
bool Budgie::CompositorSurfaceItem::renderable()
{
    return m_renderable;
}

/**
 * Get the rendering layer for this particular surface item.
 */
Budgie::RenderLayer Budgie::CompositorSurfaceItem::layer()
{
    return m_layer;
}

/**
 * Allow the compositor to update the layer
 */
void Budgie::CompositorSurfaceItem::setLayer(RenderLayer layer)
{
    m_layer = layer;
}

void Budgie::CompositorSurfaceItem::setShellSurface(QWaylandWlShellSurface *surface)
{
    m_shell_surface = surface;
    m_renderable = true;

    // Track surface title
    m_windowTitle = m_shell_surface->title();
    connect(m_shell_surface, &QWaylandWlShellSurface::titleChanged, [this] {
        m_windowTitle = m_shell_surface->title();
    });

    // TODO: Hook up stuffs
}

void Budgie::CompositorSurfaceItem::setXdgSurfacev5(QWaylandXdgSurfaceV5 *surface)
{
    m_xdg_surface_v5 = surface;
    m_renderable = true;

    // TODO: Hook up stuffs
}

/* Accessors */

/**
 * Return title for this item
 */
const QString &Budgie::CompositorSurfaceItem::title()
{
    return m_windowTitle;
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
