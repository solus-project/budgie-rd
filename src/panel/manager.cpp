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

#include "manager.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QQuickItem>

namespace Budgie::Panel
{
    Manager::Manager(int &argc, char **argv) : QApplication(argc, argv), demoWindow(new Window())
    {
        this->engine.reset(new QQmlEngine());
        auto url = QUrl::fromLocalFile("qml/panel.qml");
        this->panelComponent.reset(new QQmlComponent(engine.data(), url));
        if (panelComponent->isError()) {
            qDebug() << "Failed loading panel.qml";
            for (auto &err : panelComponent->errors()) {
                qDebug() << err;
            }
        }
        qDebug() << "I r have a manager";
    }

    void Manager::loadPanels()
    {
        /*
        QRect r = QApplication::desktop()->screenGeometry();
        demoWindow->show();
        demoWindow->updateGeometry(r);
        qDebug() << "I haz panels nao";
        */
        QQuickItem *item = qobject_cast<QQuickItem *>(panelComponent->create());
        if (!item) {
            return;
        }
        item->setParent(engine.data());
        item->setVisible(true);
    }
}
