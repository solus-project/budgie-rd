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

#include <KWindowSystem>
#include <QObject>

namespace Task
{
    class Window : public QObject
    {
        Q_OBJECT

        friend class Monitor;

        Q_PROPERTY(QString title READ title NOTIFY titleChanged)

    public:
        /**
         * Return the title for this window
         */
        const QString title();

    signals:

        void titleChanged(const QString &title);

    protected:
        /**
         * Windows must be instantiated by a Task::Monitor, and are initially
         * owned only by the monitor. Connect to signals to recieve events
         */
        explicit Window(WId id);

    private:
        WId id;
    };
}
