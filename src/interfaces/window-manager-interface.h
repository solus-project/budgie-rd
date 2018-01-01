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
    class WindowManagerInterface : public BaseInterface
    {
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
        virtual DisplayInterface *primaryDisplay() = 0;

        /**
         * Return all known displays
         */
        virtual QList<DisplayInterface *> displays() = 0;

    signals:

        /**
         * The primary display has been changed
         */
        virtual void primaryDisplayChanged() = 0;

        /**
         * A new display has been added
         */
        virtual void displayAdded(DisplayInterface *display) = 0;

        /**
         * A display has been removed.
         */
        virtual void displayRemved(DisplayInterface *display) = 0;

        /**
         * A new window has been made known to the manager.
         */
        virtual void windowAdded(WindowInterface *window) = 0;

        /*
         * The given window has been destroyed.
         */
        virtual void windowDestroyed(WindowInterface *window) = 0;
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
