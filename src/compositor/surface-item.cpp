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

#include "surface-item.h"

using namespace Budgie::Compositor;

SurfaceItem::SurfaceItem(QWaylandSurface *surface)
    : m_surface(surface), m_position(100, 150), m_size(0, 0), m_layer(RenderLayer::APPLICATION),
      m_roleConfirmed(false), m_renderable(false), m_parentItem(nullptr)
{
    // Precache
    m_size = surface->size();

    // Hook up signals
    connect(surface, &QWaylandSurface::sizeChanged, this, &SurfaceItem::sizeChanged);

    // Effectively, role change, ready to do something.
    connect(surface, &QWaylandSurface::hasContentChanged, this, &SurfaceItem::hasContentChanged);
}

QWaylandSurface *SurfaceItem::surface()
{
    return m_surface;
}

RenderLayer SurfaceItem::layer()
{
    return m_layer;
}

void SurfaceItem::setLayer(RenderLayer layer)
{
    m_layer = layer;
}

/**
 * Return the full geometry.
 */
QRect SurfaceItem::geometry()
{
    return QRect(m_position, m_size);
}

QPoint SurfaceItem::position()
{
    return m_position;
}

QSize SurfaceItem::size()
{
    return m_size;
}

bool SurfaceItem::renderable()
{
    return m_renderable;
}

bool SurfaceItem::cursor()
{
    return m_surface->isCursorSurface();
}

/**
 * wl_surface changed size, update knowledge of it.
 */
void SurfaceItem::sizeChanged()
{
    m_size = m_surface->size();
}

/**
 * Content role now available, so we're renderable
 */
void SurfaceItem::hasContentChanged()
{
    m_renderable = m_surface->hasContent();
    if (!m_renderable) {
        return;
    }
    if (m_roleConfirmed) {
        qDebug() << "Should not be setting roles again! Suggest killing client";
        return;
    }
    m_roleConfirmed = true;

    // Adjust our layer if we determine we're a cursor.
    if (cursor()) {
        setLayer(RenderLayer::CURSOR);
    }

    // Let compositor know we're ready for prime time
    emit roleConfirmed();
}

void SurfaceItem::addChild(SurfaceItem *child)
{
    qDebug() << "I now have a child :O " << child;
    child->m_parentItem = this;
    m_children << child;
}

void SurfaceItem::removeChild(SurfaceItem *child)
{
    qDebug() << "They stole my child!" << child;
    if (child->m_parentItem == this) {
        child->m_parentItem = nullptr;
    }
    m_children.removeAll(child);
}

/**
 * May well be nullptr.
 */
SurfaceItem *SurfaceItem::parentItem()
{
    return m_parentItem;
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
