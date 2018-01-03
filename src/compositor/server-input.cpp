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

#include <QEvent>

#include "server.h"

using namespace Budgie::Compositor;

/**
 * Set the active mouse focus to the given window.
 *
 * TODO: Make sure we're not in grabs or modals and give the focus to the
 * wrong folks.
 *
 * TODO2: Only issue mouse focus when a window is actually clicked into.
 *
 * Note this can be nullptr if we want to unset focus.
 */
void Server::setMouseFocus(Display *origin, Window *window)
{
    Q_UNUSED(origin);
    if (window == m_mouseFocus) {
        return;
    }

    m_mouseFocus = window;

    qDebug() << "Mouse focus set to: " << window;

    // Update mouse focus as appropriate
    QWaylandView *focusView = nullptr;
    if (origin && window) {
        focusView = origin->view(window);
    }
    m_seat->setMouseFocus(focusView);
}

/**
 * Set the active key focus to the given window.
 *
 * Note this can be nullptr if we want to unset focus.
 *
 * TODO: Only do this if we have a keyboard device.
 */
void Server::setKeyFocus(Display *origin, Window *window)
{
    Q_UNUSED(origin);
    if (window == m_keyFocus) {
        return;
    }

    m_keyFocus = window;

    QWaylandSurface *focusSurface = nullptr;

    // Update key focus as appropriate
    if (window) {
        focusSurface = window->surface();
    }
    m_seat->setKeyboardFocus(focusSurface);
}

/**
 * Search for one of our windows at the given position on the
 * specified display.
 */
Window *Server::findFocusableSurface(Display *origin, QPoint position)
{
    for (auto window : origin->inputWindows()) {
        if (window->geometry().contains(position)) {
            return window;
        }
    }
    return nullptr;
}

/**
 * Take the input event and rewrite the positions to be relative to the display.
 */
static inline void rewriteMousePosition(Display *origin, Window *window, QPointF localPos,
                                        QPointF &local, QPointF &global)
{
    const QRect geom = origin->geometry();
    const QPointF topLeft = geom.topLeft();

    // The position is always offset from the start geometry
    global = localPos + topLeft;

    // The local is deducted from window position
    local = global - window->position();
}

void Server::dispatchMouseEvent(Display *origin, QMouseEvent *e)
{
    auto window = findFocusableSurface(origin, e->pos());
    QPointF local, global;

    // When clicking, update focus.
    if (e->buttons() != Qt::NoButton) {
        setMouseFocus(origin, window);
        setKeyFocus(origin, window);
        if (origin && window) {
            origin->raiseWindow(window);
        }
    }

    if (!window) {
        return;
    }

    // Dispatch the event to the client
    switch (e->type()) {
    case QEvent::MouseButtonPress:
        m_seat->sendMousePressEvent(e->button());
        break;
    case QEvent::MouseButtonRelease:
        m_seat->sendMouseReleaseEvent(e->button());
        break;
    case QEvent::MouseMove: {
        rewriteMousePosition(origin, window, e->localPos(), local, global);
        auto view = origin->view(window);
        if (view) {
            m_seat->sendMouseMoveEvent(view, local, global);
        }
    } break;
    default:
        break;
    }
}

/**
 * Send a wheel event to the currently mouse-focusable window.
 * Note, this will not actually give the window focus.
 */
void Server::dispatchWheelEvent(Display *origin, QWheelEvent *e)
{
    auto window = findFocusableSurface(origin, e->globalPos());
    QPointF local, global;

    if (!window) {
        return;
    }

    auto angleDelta = e->angleDelta();
    int delta = 0;

    Qt::Orientation orient = angleDelta.x() == 0 ? Qt::Vertical : Qt::Horizontal;
    delta = ((orient == Qt::Vertical ? angleDelta.y() : angleDelta.x()));
    rewriteMousePosition(origin, window, e->globalPos(), local, global);
    m_seat->sendMouseWheelEvent(orient, delta);
}

void Server::dispatchTouchEvent(Display *origin, QTouchEvent *e)
{
    // TODO: Update real cursor position based on touch event
    Q_UNUSED(origin);
    Q_UNUSED(e);
}

void Server::dispatchKeyEvent(Display *origin, QKeyEvent *e)
{
    Q_UNUSED(origin);

    // Eventually we'll handle global shortcuts.
    if (!m_keyFocus) {
        return;
    }

    m_seat->sendFullKeyEvent(e);
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
