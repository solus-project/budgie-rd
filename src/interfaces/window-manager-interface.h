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

#include <QObject>

#include "base-interface.h"
#include "window-interface.h"

#define BudgieWindowManagerInterfaceIID "org.budgie-desktop.WindowManagerInterface"

namespace Budgie
{
    /**
     * The WindowManagerInterface provides a dual API used by both the shell
     * and the compositor, to define a standard way with which to build a
     * windowing environment.
     *
     * Client side use-cases (i.e. inside the shell) will operate over a
     * connection, whereas a server-side (compositor) implementation will
     * act entirely inside the compositor and relay the events *to* to clients.
     */
    class WindowManagerInterface : public QObject, public BaseInterface
    {
        Q_OBJECT

    public:
        virtual ~WindowManager()
        {
        }

        inline const QString interfaceName() override
        {
            return QStringLiteral(BudgieWindowManagerInterfaceIID);
        }

        /**
         * Return the primary display
         */
        virtual DisplayInterface *primaryDisplay();

        /**
         * Return all known displays
         */
        virtual QList<DisplayInterface *> displays();

    signals:

        /**
         * The primary display has been changed
         */
        void primaryDisplayChanged();

        /**
         * A new display has been added
         */
        void displayAdded(DisplayInterface *display);

        /**
         * A display has been removed.
         */
        void displayRemved(DisplayInterface *display);

        /**
         * A new window has been made known to the manager.
         */
        void windowAdded(WindowInterface *window);

        /*
         * The given window has been destroyed.
         */
        void windowDestroyed(WindowInterface *window);
    };
}

Q_DECLARE_INTERFACE(Budgie::WindowManagerInterface, BudgieWindowManagerInterfaceIID)

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
