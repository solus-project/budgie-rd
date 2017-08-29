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

#include "raven.h"

#include <KWindowEffects>
#include <QBoxLayout>
#include <QDebug>
#include <QLabel>

namespace Raven
{
    Window::Window()
    {
        // Push dock-type bits bits
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_X11NetWmWindowTypeDock);
        setAttribute(Qt::WA_ShowWithoutActivating);
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
        setFocusPolicy(Qt::NoFocus);
        setFixedSize(0, 0);

        packArea = new QWidget(this);
        setLayout(new QHBoxLayout());
        layout()->setMargin(0);
        layout()->addWidget(packArea);

        packArea->setObjectName("packArea");
        packArea->setStyleSheet("#packArea { background-color: rgba(255, 255, 255, 85%); }");
        packArea->setLayout(new QVBoxLayout());
        packArea->layout()->setMargin(0);

        auto layout = qobject_cast<QVBoxLayout *>(packArea->layout());
        auto labelr = new QLabel("I could be your next Raven ... ");
        labelr->setStyleSheet("color: black;");
        layout->addWidget(labelr, 0, Qt::AlignHCenter | Qt::AlignVCenter);
    }

    void Window::updateGeometry(QRect &rect)
    {
        QRect finalPosition;

        // We're always on the RHS for now with a size equalling 15% of width
        int width = (int)(rect.width() * 0.15);
        finalPosition.setX((rect.x() + rect.width()) - width);
        finalPosition.setY(rect.y());
        finalPosition.setHeight(rect.height() - 37);
        finalPosition.setWidth(width);

        setFixedSize(finalPosition.width(), finalPosition.height());
        move(finalPosition.x(), finalPosition.y());

        // Be a tart, show off blurs
        KWindowEffects::enableBlurBehind(effectiveWinId());
        KWindowEffects::slideWindow(this, KWindowEffects::SlideFromLocation::RightEdge);
    }
}
