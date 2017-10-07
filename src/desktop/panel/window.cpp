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
        : intendedSize(37), desktopIface(desktopIface), orient(Qt::Horizontal)
    {
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
        rootWidget->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
        rootWidget->layout()->setMargin(0);
    }

    void Window::insertApplet(Applet *applet)
    {
        static auto appletAlign = Qt::AlignLeft | Qt::AlignTop;

        auto layout = qobject_cast<QBoxLayout *>(this->rootWidget->layout());
        applet->setParent(rootWidget);
        layout->addWidget(applet, 0, appletAlign);
        applet->setOrientation(this->orient);
        applet->setDesktopInterface(this->desktopIface);
        applet->show();
        applets.append(applet);
    }

    void Window::updateGeometry(QRect &rect, Position p)
    {
        QRect finalPosition;
        // TODO: Listen for changes to the window ID to reset all dock + strut bits
        auto wid = winId();
        QBoxLayout::Direction dir = QBoxLayout::LeftToRight;
        Qt::Orientation orient = Qt::Horizontal;

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
            dir = QBoxLayout::TopToBottom;
            orient = Qt::Vertical;
            break;
        case Position::Right:
            finalPosition.setX((rect.x() + rect.width()) - intendedSize);
            finalPosition.setY(rect.y());
            finalPosition.setWidth(intendedSize);
            finalPosition.setHeight(rect.height());
            KWindowSystem::setStrut(wid, 0, intendedSize, 0, 0);
            dir = QBoxLayout::TopToBottom;
            orient = Qt::Vertical;
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

        auto layout = qobject_cast<QBoxLayout *>(rootWidget->layout());
        if (dir != layout->direction()) {
            layout->setDirection(dir);
        }

        // TODO: Make a proper notify list
        if (this->orient != orient) {
            this->orient = orient;
            for (const auto &applet : applets) {
                applet->setOrientation(this->orient);
            }
        }

        setFixedSize(finalPosition.width(), finalPosition.height());
        move(finalPosition.x(), finalPosition.y());

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
