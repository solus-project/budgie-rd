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

#include <QDebug>

#include "wayland-window-wl-shell.h"
#include "wayland-window-xdg-shell-v5.h"
#include "wayland-window.h"

using namespace Budgie::Compositor;

/**
 * Default constructor.
 */
WaylandWindow::WaylandWindow(SurfaceItem *rootSurface)
    : m_rootSurface(rootSurface), m_layer(RenderLayer::APPLICATION), m_position(150, 100)
{
    // Initial opacity
    m_opacity = 1.0;
    m_scale = QVector2D(1.0, 1.0);
}

/**
 * Return the surface considered to be our root.
 * This surface may in turn have more ancestors.
 */
SurfaceItem *WaylandWindow::rootSurface()
{
    return m_rootSurface;
}

WaylandWindow *WaylandWindow::create(SurfaceItem *surface, QWaylandWlShellSurface *wl_shell)
{
    return new WaylandWindowWlShell(surface, wl_shell);
}

WaylandWindow *WaylandWindow::create(SurfaceItem *surface, QWaylandXdgSurfaceV5 *xdg_shell)
{
    return new WaylandWindowXdgShellV5(surface, xdg_shell);
}

/**
 * Return the position of this WaylandWindow within the virtual coordinate
 * system.
 *
 */
QPoint WaylandWindow::position()
{
    return m_position;
}

void WaylandWindow::setPosition(QPoint position)
{
    m_position = position;
}

/**
 * Return the geometry of this WaylandWindow within the virtual coordinate
 * system.
 *
 * TODO: Split the rootSurface coordinates from our own.
 */
QRect WaylandWindow::geometry()
{
    return QRect(m_position, size());
}

/**
 * Return the geometry of this WaylandWindow within the virtual coordinate
 * system.
 *
 * TODO: Split the rootSurface coordinates from our own.
 */
QSize WaylandWindow::size()
{
    return m_rootSurface->size();
}

void WaylandWindow::setLayer(RenderLayer layer)
{
    m_layer = layer;
}

RenderLayer WaylandWindow::layer()
{
    return m_layer;
}

/**
 * This is to help the renderers perform drawing in a correct fashion
 * and making sure each surface gets the frames sent to it in the right
 * order.
 */
void WaylandWindow::surfaceForeach(QObject *instance, SurfaceFunctor f)
{
    if (!f) {
        return;
    }

    // For now we're just going to pass the rootSurface
    (instance->*f)(this, rootSurface());
}

double WaylandWindow::opacity()
{
    return m_opacity;
}

void WaylandWindow::setOpacity(double opacity)
{
    if (opacity == m_opacity) {
        return;
    }
    m_opacity = opacity;
    emit opacityChanged();
    emit animationTick();
}

QVector2D WaylandWindow::scale()
{
    return m_scale;
}

void WaylandWindow::setScale(QVector2D scale)
{
    if (scale == m_scale) {
        return;
    }
    m_scale = scale;
    emit scaleChanged();
    emit animationTick();
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
