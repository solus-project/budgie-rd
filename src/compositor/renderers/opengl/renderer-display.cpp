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

#include "renderer-display.h"

using namespace Budgie::Compositor;

OpenGLDisplay::OpenGLDisplay(QWaylandOutput *output) : Display(output, this)
{
    connect(output, &QWaylandOutput::currentModeChanged, this, &OpenGLDisplay::currentModeChanged);
}

void OpenGLDisplay::mapWindow(Compositor::Window *window)
{
    qDebug() << "Mapped:" << window;
}

void OpenGLDisplay::unmapWindow(Compositor::Window *window)
{
    qDebug() << "Unmapped: " << window;
}

void OpenGLDisplay::currentModeChanged()
{
    auto mode = output()->currentMode();
    auto geom = mode.size();
    resize(geom.width(), geom.height());
    setPosition(output()->position());
    qDebug() << "New mode:" << geom;
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
