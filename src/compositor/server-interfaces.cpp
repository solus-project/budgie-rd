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

    auto window = new Compositor::Window(surface);
    qDebug() << "Added surface:" << window;

    // TODO: Decide which output we wanna put this guy on and map it there.
    m_surfaces.insert(surface, QSharedPointer<Compositor::Window>(window));

    // Le Hacky Demos
    auto view = m_displays[0]->mapWindow(window);
    if (!view) {
        return;
    }
    view->setOutput(m_displays[0]->output());
    view->setPrimary();

    // TODO: Only allocate when we really need this..
    window->setLayer(RenderLayer::APPLICATION);
    m_renderables[window->layer()] << window;
}

/**
 * The WaylandSurface is about to be destroyed, so we must remove knowledge
 * of this from ourselves and all displays
 */
void Server::surfaceDestroying(QWaylandSurface *surface)
{
    auto window = m_surfaces.value(surface, nullptr);
    if (!window) {
        qWarning() << "Accounting error: Don't know about " << surface;
        return;
    }

    // Remove window from all displays
    for (auto &display : m_displays) {
        // TODO: If the display contains then unmap
        display->unmapWindow(window.data());
    }

    qDebug() << "Removed surface:" << window.data();

    // TODO: Cycle focus to the next available candidate instead.
    if (window.data() == m_keyFocus) {
        setKeyFocus(nullptr, nullptr);
    }
    if (window.data() == m_mouseFocus) {
        setMouseFocus(nullptr, nullptr);
    }

    // Drop from the renderables
    m_renderables[window->layer()].removeAll(window.data());
    m_surfaces.remove(surface);
}

void Server::wlShellCreated(QWaylandWlShellSurface *shell)
{
    Q_UNUSED(shell);
}

void Server::xdgShellv5Created(QWaylandXdgSurfaceV5 *shell)
{
    Q_UNUSED(shell);
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
    Q_UNUSED(oldSeat);
    qDebug() << "Seat set to: " << newSeat;
    m_seat = newSeat;
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
