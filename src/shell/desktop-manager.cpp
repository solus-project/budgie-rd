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

#include "desktop-manager.h"

#include <QDebug>
#include <QDesktopWidget>

namespace Desktop
{
    Manager::Manager(QQmlEngine *engine)
        : engine(engine), panelManager(new Panel::Manager(engine)), numScreens(0), primaryScreen(0)
    {
        auto desktop = QApplication::desktop();

        // Hook up signals we care about
        connect(desktop,
                &QDesktopWidget::primaryScreenChanged,
                this,
                &Manager::primaryScreenChanged);
        connect(desktop, &QDesktopWidget::screenCountChanged, this, &Manager::screenCountChanged);
        connect(desktop, &QDesktopWidget::resized, this, &Manager::resized);

        // Forcibly invoke the signal handlers
        primaryScreenChanged();
        screenCountChanged(desktop->screenCount());

        updateGeometry();
    }

    void Manager::updateGeometry()
    {
        auto desktop = QApplication::desktop();
        qDebug() << "numScreens: " << numScreens;
        QRect r = desktop->screenGeometry();
        raven.show();
        raven.updateGeometry(r);
        panelManager->loadPanels();
    }

    /**
     * Primary monitor has changed so re-evaluate placement of panel & raven
     */
    void Manager::primaryScreenChanged()
    {
        auto desktop = qobject_cast<QDesktopWidget *>(sender());
        primaryScreen = desktop->primaryScreen();
        qDebug() << "New primary: " << primaryScreen;
    }

    /**
     * The number of available screens has changed
     */
    void Manager::screenCountChanged(int newCount)
    {
        qDebug() << "Screen count: " << newCount;

        if (newCount < numScreens) {
            for (int i = numScreens - 1; i > newCount - 1; i--) {
                qDebug() << "Removed screen: " << i;
                rootWindows.remove(i);
            }
        }

        numScreens = newCount;

        for (int i = 0; i < numScreens; i++) {
            if (!rootWindows.contains(i)) {
                rootWindows.insert(i, QSharedPointer<RootWindow>(new RootWindow(engine, i)));
            }
            rootWindows[i]->updateGeometry();
        }
    }

    void Manager::resized(int screen)
    {
        qDebug() << "Resized screen: " << screen;
        if (!rootWindows.contains(screen)) {
            qDebug() << "Unknown screen index: " << screen;
            return;
        }
        rootWindows[screen]->updateGeometry();
    }
}
