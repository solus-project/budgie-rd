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

#include "../panel/manager.h"
#include "../raven/raven.h"

#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Budgie::Panel::Manager manager;
    Raven::Window raven;
    manager.loadPanels();

    // TODO: Add DesktopManager for panels + raven alike within shell component
    QRect r = QApplication::desktop()->screenGeometry();
    raven.updateGeometry(r);
    raven.show();

    return app.exec();
}
