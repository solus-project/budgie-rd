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

#include "desktop-manager.h"

#include <QDebug>
#include <QDesktopWidget>

namespace Desktop
{
    Manager::Manager() : numScreens(0)
    {
        QGuiApplication *app = qobject_cast<QGuiApplication *>(QCoreApplication::instance());

        // Hook up signals we care about
        connect(app, &QGuiApplication::primaryScreenChanged, this, &Manager::primaryScreenChanged);
        connect(app, &QGuiApplication::screenAdded, this, &Manager::screenAdded);
        connect(app, &QGuiApplication::screenRemoved, this, &Manager::screenRemoved);

        updateGeometry();
    }

    void Manager::updateGeometry()
    {
        auto desktop = QApplication::desktop();
        numScreens = desktop->screenCount();
        qDebug() << "numScreens: " << numScreens;
        QRect r = desktop->screenGeometry();
        raven.show();
        raven.updateGeometry(r);
        panelManager.loadPanels();
    }

    /**
     * Primary monitor has changed so re-evaluate placement of panel & raven
     */
    void Manager::primaryScreenChanged(QScreen *screen)
    {
        Q_UNUSED(screen);
    }

    /**
     * A new screen was made available
     */
    void Manager::screenAdded(QScreen *screen)
    {
        Q_UNUSED(screen);
    }

    /**
     * An existing screen has been removed
     */
    void Manager::screenRemoved(QScreen *screen)
    {
        Q_UNUSED(screen);
    }
}
