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

#include "server.h"

using namespace Budgie::Compositor;

void Server::surfaceCreated(QWaylandSurface *surface)
{
    if (m_surfaces.contains(surface)) {
        qWarning() << "Accounting error: Already know about " << surface;
        return;
    }

    auto item = new Compositor::SurfaceItem(surface);
    qDebug() << "Added surface:" << item;

    // Cache the new surface
    m_surfaces.insert(surface, QSharedPointer<Compositor::SurfaceItem>(item));
    connect(surface, &QWaylandSurface::childAdded, this, &Server::surfaceChildAdded);
    connect(surface, &QWaylandSurface::parentChanged, this, &Server::surfaceParentChanged);

    // Find the right display to map the new surface to and ensure it gets
    // mapped there.
    // TODO: Consider leaving the mapping until we know this is some kind of
    // child, cursor, or toplevel, so that we map an entire window in one go.
    auto display = initialDisplay(item);
    auto view = display->mapSurfaceItem(item);
    if (!view) {
        return;
    }
    view->setOutput(display->output());
    view->setPrimary();
}

/**
 * The WaylandSurface is about to be destroyed, so we must remove knowledge
 * of this from ourselves and all displays
 */
void Server::surfaceDestroying(QWaylandSurface *surface)
{
    auto item = m_surfaces.value(surface, nullptr);
    if (!item) {
        qWarning() << "Accounting error: Don't know about " << surface;
        return;
    }

    // Might be a subsurface being destroyed, so remove it from the parent.
    auto parent = item->parentItem();
    if (parent) {
        parent->removeChild(item.data());
    }

    // We may or may not have a window for this
    auto window = m_windows.value(item.data(), nullptr);

    // Remove item from all displays
    for (auto &display : m_displays) {
        // Ask it be unmapped first.
        if (window) {
            display->unmapWindow(window.data());
        }
        display->unmapSurfaceItem(item.data());
    }

    qDebug() << "Removed surface:" << item.data();

    // TODO: Cycle focus to the next available candidate instead.
    if (item.data() == m_keyFocus) {
        setKeyFocus(nullptr, nullptr);
    }
    if (item.data() == m_mouseFocus) {
        setMouseFocus(nullptr, nullptr);
    }

    // Remove from the window first (if we have it.)
    m_windows.remove(item.data());

    // Remove from the surface cache
    m_surfaces.remove(surface);
}

/**
 * A new wl_shell window has been constructed.
 * At this point we will associate it with a WaylandWindow and make it
 * a candidate for rendering.
 */
void Server::wlShellCreated(QWaylandWlShellSurface *shell)
{
    auto surface = m_surfaces.value(shell->surface(), nullptr);
    if (!surface) {
        qWarning() << "Shell surface for unknown client. Recommend you kill!";
        return;
    }
    promoteWindow(WaylandWindow::create(surface.data(), shell));
}

/**
 * New xdg surface has been constructed, do the same thing as we'd do
 * for a normal wl_shell window.
 */
void Server::xdgShellv5Created(QWaylandXdgSurfaceV5 *shell)
{
    auto surface = m_surfaces.value(shell->surface(), nullptr);
    if (!surface) {
        qWarning() << "XDG surface for unknown client. Recommend you kill!";
        return;
    }
    promoteWindow(WaylandWindow::create(surface.data(), shell));
}

/**
 * We've been created so we need to get ready to show stuff on screen.
 */
void Server::wlCreated()
{
    if (!isCreated()) {
        return;
    }
    // Enforce some kind of seat knowledge.
    wlSeatChanged(defaultSeat(), nullptr);
}

/**
 * Handle seat changes. In future we'll need to rebind active focus and such
 * and remove knowledge of the old seat from existing clients. For now, just
 * stash the pointer.
 */
void Server::wlSeatChanged(QWaylandSeat *newSeat, QWaylandSeat *oldSeat)
{
    if (oldSeat) {
        disconnect(oldSeat, &QWaylandSeat::cursorSurfaceRequest, this, &Server::wlCursorChanged);
    }
    qDebug() << "Seat set to: " << newSeat;
    m_seat = newSeat;
    connect(m_seat, &QWaylandSeat::cursorSurfaceRequest, this, &Server::wlCursorChanged);
}

/* Subsurfaces */
void Server::surfaceChildAdded(QWaylandSurface *childSurface)
{
    QWaylandSurface *parent = qobject_cast<QWaylandSurface *>(sender());
    auto parentItem = m_surfaces.value(parent, nullptr);
    auto childItem = m_surfaces.value(childSurface, nullptr);

    if (!parentItem || !childItem) {
        qDebug() << "Accounting error in surfaceChildAdded!";
        return;
    }

    // Add the child to the given parent
    parentItem->addChild(childItem.data());
}

void Server::surfaceParentChanged(QWaylandSurface *oldParent, QWaylandSurface *newParent)
{
    Q_UNUSED(newParent);

    QWaylandSurface *child = qobject_cast<QWaylandSurface *>(sender());
    auto childItem = m_surfaces.value(child, nullptr);
    auto oldItem = m_surfaces.value(oldParent, nullptr);

    if (!childItem || !oldItem) {
        qDebug() << "Accounting error in surfaceParentChanged!";
        return;
    }

    // Remove the child from the old parent
    oldItem->removeChild(childItem.data());
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
