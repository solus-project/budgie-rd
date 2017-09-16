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
#include <QQuickItem>

namespace Raven
{
    Window::Window() : position(Position::Left)
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

        // Hook up signals from QML land
        QQuickItem *rootObj = rootObject();
        connect(rootObj, SIGNAL(dismiss()), this, SLOT(handleDismiss()));
    }

    void Window::handleDismiss()
    {
        qDebug() << "Raven go bye bye";
        KWindowEffects::slideWindow(winId(), KWindowEffects::SlideFromLocation::RightEdge, 0);
        hide();
    }

    void Window::updateGeometry(QRect &rect)
    {
        QRect finalPosition;

        KWindowEffects::slideWindow(winId(), KWindowEffects::SlideFromLocation::RightEdge, 0);

        // We're always on the RHS for now with a size equalling 15% of width
        int width = (int)(rect.width() * 0.18);
        if (position == Position::Right) {
            finalPosition.setX((rect.x() + rect.width()) - width);
        } else {
            finalPosition.setX(rect.x());
        }
        finalPosition.setY(rect.y());
        finalPosition.setHeight(rect.height());
        finalPosition.setWidth(width);

        setMaximumWidth(finalPosition.width());
        setMaximumHeight(finalPosition.height());
        setWidth(finalPosition.width());
        setHeight(finalPosition.height());
        setPosition(finalPosition.x(), finalPosition.y());

        // Be a tart, show off blurs
        KWindowEffects::enableBlurBehind(winId());
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
