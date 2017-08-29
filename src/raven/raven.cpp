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
        // https://bugreports.qt.io/browse/QTBUG-54886
        //         setAttribute(Qt::WA_ShowWithoutActivating);
        setProperty("_q_showWithoutActivating", QVariant(true));
        setFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool |
                 Qt::BypassWindowManagerHint);
        // Parent size dictates QML size
        resize(0, 0);
        setResizeMode(QQuickView::SizeRootObjectToView);
        setClearBeforeRendering(true);
        setColor(QColor(Qt::transparent));
        setSource(QUrl("qrc:/qml/raven.qml"));
    }

    void Window::updateGeometry(QRect &rect)
    {
        QRect finalPosition;

        KWindowEffects::slideWindow(winId(), KWindowEffects::SlideFromLocation::RightEdge, 0);

        // We're always on the RHS for now with a size equalling 15% of width
        int width = (int)(rect.width() * 0.15);
        finalPosition.setX((rect.x() + rect.width()) - width);
        finalPosition.setY(rect.y());
        finalPosition.setHeight(rect.height());
        finalPosition.setWidth(width);

        setMaximumWidth(finalPosition.width());
        setMaximumHeight(finalPosition.height() - 37);
        setWidth(finalPosition.width());
        setHeight(finalPosition.height() - 37);
        setPosition(finalPosition.x(), finalPosition.y());

        // Be a tart, show off blurs
        KWindowEffects::enableBlurBehind(winId());
    }
}
