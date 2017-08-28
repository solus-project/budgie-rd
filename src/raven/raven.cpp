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

#include "raven.h"

#include <QBoxLayout>
#include <QDebug>

namespace Raven
{
    Window::Window()
    {
        // Push dock-type bits bits
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_X11NetWmWindowTypeDock);
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
    }

    void Window::updateGeometry(QRect &rect)
    {
        QRect finalPosition;

        // We're always on the RHS for now with a size equalling 15% of width
        int width = (int)(rect.width() * 0.15);
        finalPosition.setX((rect.x() + rect.width()) - width);
        finalPosition.setY(rect.y());
        finalPosition.setHeight(rect.height());
        finalPosition.setWidth(width);

        setFixedSize(finalPosition.width(), finalPosition.height());
        move(finalPosition.x(), finalPosition.y());
    }
}
