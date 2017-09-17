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

#pragma once

#include "../lib/manager.h"

#include <QWidget>

namespace Panel
{
    class Applet : public QWidget
    {
        Q_OBJECT

        friend class Window;

        Q_PROPERTY(Qt::Orientation orientation READ orientation NOTIFY orientationChanged)

    public:
        explicit Applet(QWidget *parent = nullptr);

        Qt::Orientation orientation();

        /**
         * Allow applets to access the desktop management
         *
         * TODO: Hide all of these Things as methods of a single opaque object
         * that we pass the applets on initialisation as the relationship is
         * quite warped.
         */
        const Desktop::ManagerInterface *desktop();

    protected:
        void setOrientation(Qt::Orientation orient);
        void setDesktopInterface(Desktop::ManagerInterface *iface);

    signals:
        void orientationChanged(Qt::Orientation orient);

    private:
        Qt::Orientation appletOrientation;
        Desktop::ManagerInterface *desktopIface;
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
