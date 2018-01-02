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

/**
 * New display is added so hook up the relevant handlers
 */
void Server::connectDisplay(Display *display)
{
    // Mouse events
    connect(display, &Display::inputMouseMoved, this, &Server::inputMouseMoved);
    connect(display, &Display::inputMousePressed, this, &Server::inputMousePressed);
    connect(display, &Display::inputMouseReleased, this, &Server::inputMouseReleased);

    // Keyboard events
    connect(display, &Display::inputKeyPressed, this, &Server::inputKeyPressed);
    connect(display, &Display::inputKeyReleased, this, &Server::inputKeyReleased);

    // Touch events
    connect(display, &Display::inputTouched, this, &Server::inputTouched);
}

/**
 * Dispatch mouse move to currently focused surface
 */
void Server::inputMouseMoved(QMouseEvent *e)
{
    Q_UNUSED(e);
}

/**
 * Dispatch mouse press to currently focused surface
 */
void Server::inputMousePressed(QMouseEvent *e)
{
    Q_UNUSED(e);
}

/**
 * Dispatch mouse release to currently focused surface
 */
void Server::inputMouseReleased(QMouseEvent *e)
{
    Q_UNUSED(e);
}

/**
 * Dispatch key press to currently focused surface
 */
void Server::inputKeyPressed(QKeyEvent *e)
{
    Q_UNUSED(e);
}

/**
 * Dispatch key release to currently focused surface
 */
void Server::inputKeyReleased(QKeyEvent *e)
{
    Q_UNUSED(e);
}

/**
 * Dispatch touch event to currently focused surface
 */
void Server::inputTouched(QTouchEvent *e)
{
    Q_UNUSED(e);
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
