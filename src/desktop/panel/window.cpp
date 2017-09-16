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

#include "window.h"
#include "tasklist/tasklist.h"

#include <KWindowEffects>
#include <KWindowSystem>
#include <QDebug>
#include <QHBoxLayout>

namespace Panel
{
    Window::Window(Desktop::ManagerInterface *desktopIface)
        : intendedSize(37), desktopIface(desktopIface)
    {
        qDebug() << "I r have a panel";
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_X11NetWmWindowTypeDock);
        setAttribute(Qt::WA_X11DoNotAcceptFocus);
        setAttribute(Qt::WA_ShowWithoutActivating);
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setFocusPolicy(Qt::NoFocus);
        setFixedSize(0, 0);
        // Parent size dictates QML size
        resize(0, 0);

        rootWidget = new QWidget(this);
        auto layout = new QHBoxLayout;
        this->setLayout(layout);
        layout->addWidget(rootWidget);
        layout->setMargin(0);

        rootWidget->setObjectName("budgie-panel");
        rootWidget->setStyleSheet("#budgie-panel { background-color: rgba(0, 0, 0, 0.8); }");

        rootWidget->setLayout(new QHBoxLayout);
        rootWidget->layout()->setMargin(0);

        this->demoCode();
    }

    void Window::demoCode()
    {
        qDebug() << "Spawning a tasklist applet";
        auto applet = new TasklistApplet();
        applet->setParent(rootWidget);
        rootWidget->layout()->addWidget(applet);
        applet->show();
    }

    void Window::updateGeometry(QRect &rect, Position p)
    {
        QRect finalPosition;
        // TODO: Listen for changes to the window ID to reset all dock + strut bits
        auto wid = winId();

        KWindowEffects::slideWindow(wid, KWindowEffects::SlideFromLocation::BottomEdge, 0);

        // TODO: Switch to extended struts
        switch (p) {
        case Position::Top:
            finalPosition.setX(rect.x());
            finalPosition.setY(rect.y());
            finalPosition.setWidth(rect.width());
            finalPosition.setHeight(intendedSize);
            KWindowSystem::setStrut(wid, 0, 0, intendedSize, 0);
            break;
        case Position::Left:
            finalPosition.setX(rect.x());
            finalPosition.setY(rect.y());
            finalPosition.setWidth(intendedSize);
            finalPosition.setHeight(rect.height());
            KWindowSystem::setStrut(wid, intendedSize, 0, 0, 0);
            break;
        case Position::Right:
            finalPosition.setX((rect.x() + rect.width()) - intendedSize);
            finalPosition.setY(rect.y());
            finalPosition.setWidth(intendedSize);
            finalPosition.setHeight(rect.height());
            KWindowSystem::setStrut(wid, 0, intendedSize, 0, 0);
            break;
        case Position::Bottom:
        default:
            finalPosition.setX(rect.x());
            finalPosition.setY((rect.y() + rect.height()) - intendedSize);
            finalPosition.setWidth(rect.width());
            finalPosition.setHeight(intendedSize);
            KWindowSystem::setStrut(wid, 0, 0, 0, intendedSize);
            break;
        }
        setFixedSize(finalPosition.width(), finalPosition.height());
        move(finalPosition.x(), finalPosition.y());

        qDebug() << "Update geom plox: " << finalPosition << " @ " << p;

        // Be a tart, show off blurs
        KWindowEffects::enableBlurBehind(wid);
        KWindowSystem::setType(wid, NET::WindowType::Dock);
    }

    /**
     * Just pass it back off to the DesktopManager implementation
     */
    void Window::handleRavenToggle()
    {
        desktopIface->toggleRaven();
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
