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

#include "window.h"

using namespace Budgie::Compositor;

Window::Window(QWaylandSurface *surface) : m_surface(surface), m_position(100, 300), m_size(0, 0)
{
    // Precache
    m_size = surface->size();

    // Hook up signals
    connect(surface, &QWaylandSurface::sizeChanged, this, &Window::sizeChanged);
}

QWaylandSurface *Window::surface()
{
    return m_surface;
}

/**
 * Return the full geometry.
 */
QRect Window::geometry()
{
    return QRect(m_position, m_size);
}

QPoint Window::position()
{
    return m_position;
}

QSize Window::size()
{
    return m_size;
}

/**
 * wl_surface changed size, update knowledge of it.
 */
void Window::sizeChanged()
{
    m_size = m_surface->size();
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
