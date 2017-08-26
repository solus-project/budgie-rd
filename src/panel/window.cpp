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

#include "window.h"
#include <KWindowSystem>
#include <QBoxLayout>
#include <QDebug>
#include <QPushButton>

namespace Budgie::Panel
{
    Window::Window() : intendedSize(42)
    {
        qDebug() << "I r have a panel";

        // Push dock bits
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_X11NetWmWindowTypeDock);
        setAttribute(Qt::WA_X11DoNotAcceptFocus);
        setAttribute(Qt::WA_ShowWithoutActivating);
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setFocusPolicy(Qt::NoFocus);
        setFixedSize(0, 0);

        packArea = new QWidget(this);
        setLayout(new QHBoxLayout());
        layout()->setMargin(0);
        layout()->addWidget(packArea);

        packArea->setObjectName("packArea");
        packArea->setStyleSheet("#packArea { background-color: rgba(0, 0, 0, 75%); }");

        packArea->setLayout(new QHBoxLayout());
        packArea->layout()->setMargin(0);

        this->demoCode();
    }

    void Window::demoCode()
    {
        auto widget = new QPushButton("Menu");
        widget->setIcon(QIcon::fromTheme("open-menu"));
        widget->setStyleSheet("color: white;");
        widget->setFlat(true);
        auto layout = qobject_cast<QHBoxLayout *>(packArea->layout());
        layout->addWidget(widget, 0, Qt::AlignLeft | Qt::AlignVCenter);
    }

    void Window::updateGeometry(QRect &rect, Position p)
    {
        QRect finalPosition;
        // TODO: Listen for changes to the window ID to reset all dock + strut bits
        auto wid = effectiveWinId();

        // TODO: Switch to extended struts
        switch (p) {
        case Position::Top:
            finalPosition.setX(rect.x());
            finalPosition.setY(rect.y());
            finalPosition.setWidth(rect.width());
            finalPosition.setHeight(intendedSize);
            KWindowSystem::setStrut(wid, 0, 0, intendedSize, 0);
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
    }
}
