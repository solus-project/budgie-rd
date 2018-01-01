/*
 * This file is part of budgie-rd
 *
 * Copyright © 2017-2018 Budgie Desktop Developers
 *
 * budgie-rd is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#pragma once

#include "../lib/manager.h"
#include "../taskmon/task-monitor.h"
#include "applet.h"

#include <QWidget>

namespace Panel
{
    Q_NAMESPACE

    enum Position {
        Undetermined,
        Top,
        Left,
        Right,
        Bottom,
    };

    Q_ENUM_NS(Position)

    class Window : public QWidget
    {
        Q_OBJECT

    public:
        explicit Window(Desktop::ManagerInterface *desktopIface);
        void updateGeometry(QRect &rect, Position p = Position::Bottom);

    private:
        int intendedSize;
        Desktop::ManagerInterface *desktopIface;
        QWidget *rootWidget;
        void insertApplet(Applet *applet);
        Qt::Orientation orient;

        // In future use UUID -> Applet QHash
        QList<Applet *> applets;

    private slots:
        void handleRavenToggle();
    };
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
