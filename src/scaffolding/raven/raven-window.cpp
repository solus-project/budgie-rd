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

#include "raven-window.h"

Budgie::RavenWindow::RavenWindow(ShellInterface *interface) : m_shell(interface)
{
    move(1920 - 400, 0);
    setFixedSize(400, 1080 - 30);
    setAttribute(Qt::WA_X11NetWmWindowTypeDock);
    setAttribute(Qt::WA_X11DoNotAcceptFocus);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setFocusPolicy(Qt::NoFocus);
}

Budgie::RavenWindow::~RavenWindow()
{
}

void Budgie::RavenWindow::show()
{
    QWidget::show();
}

void Budgie::RavenWindow::hide()
{
    QWidget::hide();
}

void Budgie::RavenWindow::toggle()
{
    if (!isVisible()) {
        QWidget::show();
    } else {
        QWidget::hide();
    }
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
