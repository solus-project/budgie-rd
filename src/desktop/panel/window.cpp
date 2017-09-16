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
#include <KWindowEffects>
#include <KWindowSystem>
#include <QBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QQuickItem>

namespace Panel
{
    Window::Window(Desktop::ManagerInterface *desktopIface, QQmlEngine *engine)
        : QQuickView(engine, nullptr), intendedSize(37), desktopIface(desktopIface)
    {
        qDebug() << "I r have a panel";
        // https://bugreports.qt.io/browse/QTBUG-54886
        //         setAttribute(Qt::WA_ShowWithoutActivating);
        setProperty("_q_showWithoutActivating", QVariant(true));
        setFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
        // Parent size dictates QML size
        resize(0, 0);
        setResizeMode(QQuickView::SizeRootObjectToView);
        setClearBeforeRendering(true);
        setColor(QColor(Qt::transparent));
        setSource(QUrl("qrc:/qml/panel.qml"));

        // Hook up signals from QML land
        QQuickItem *rootObj = rootObject();
        connect(rootObj, SIGNAL(toggleRaven()), this, SLOT(handleRavenToggle()));

        this->demoCode();
    }

    void Window::demoCode()
    {
        // Test task monitor
        monitor.reset(new Task::Monitor());
        connect(monitor.data(), &Task::Monitor::windowOpened, this, &Window::windowOpened);
        connect(monitor.data(), &Task::Monitor::windowClosed, this, &Window::windowClosed);
        monitor->notifyAll();
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
        setMaximumWidth(finalPosition.width());
        setMaximumHeight(finalPosition.height());
        setWidth(finalPosition.width());
        setHeight(finalPosition.height());
        setPosition(finalPosition.x(), finalPosition.y());

        qDebug() << "Update geom plox: " << finalPosition << " @ " << p;

        // Be a tart, show off blurs
        KWindowEffects::enableBlurBehind(wid);
        KWindowSystem::setType(wid, NET::WindowType::Dock);
    }

    void Window::windowOpened(Task::Window *window)
    {
        qDebug() << "Window opened: " << window->title();
    }

    void Window::windowClosed(Task::Window *window)
    {
        qDebug() << "Window closed: " << window->title();
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
