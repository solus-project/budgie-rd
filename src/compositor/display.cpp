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

#include "display.h"

using namespace Budgie::Compositor;

Display::Display(QWaylandOutput *output, QWindow *window) : m_output(output), m_window(window)
{
    if (window != nullptr) {
        output->setWindow(window);
    }
}

QWaylandOutput *Display::output()
{
    return m_output.data();
}

/**
 * Ok so the header file lies, we'll update this to have a real index in time.
 */
uint Display::index()
{
    return 0;
}

QRect Display::geometry()
{
    return m_output->geometry();
}

QWindow *Display::window()
{
    return m_window;
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
