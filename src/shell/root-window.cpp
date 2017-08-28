/*
 * This file is part of budgie-rd
 *
 * Copyright © 2017 Ikey Doherty <ikey@solus-project.com>
 *
 * budgie-rd is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#include "root-window.h"

#include <KWindowSystem>
#include <QApplication>
#include <QDesktopWidget>

namespace Desktop
{
    RootWindow::RootWindow(int screenNumber) : screenNumber(screenNumber)
    {
        setFixedSize(0, 0);
    }

    void RootWindow::updateGeometry()
    {
        hide();
        auto desktop = QApplication::desktop();
        // Copy our geom from the target geom
        this->visibleArea = desktop->screenGeometry(this->screenNumber);
        move(visibleArea.x(), visibleArea.y());
        setFixedSize(visibleArea.width(), visibleArea.height());
        show();

        // TODO: Track wID changes
        KWindowSystem::setType(effectiveWinId(), NET::WindowType::Desktop);
    }
}
