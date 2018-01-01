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

#include <KWindowSystem>
#include <QObject>

namespace Task
{
    class Window : public QObject
    {
        Q_OBJECT

        friend class Monitor;

        Q_PROPERTY(QString title READ title NOTIFY titleChanged)
        Q_PROPERTY(QString icon READ title NOTIFY iconNameChanged)

    public:
        /**
         * Return the title for this window
         */
        const QString title();

        /**
         * Icon name as set by the client.
         */
        const QString iconName();

        /**
         * Wether this window has active focus or not.
         */
        const bool active();

        const bool minimized();

    public slots:

        /**
         * Close window
         */
        void close();

        /**
         * Minimize window
         */
        void minimize();

        /**
         * Unminimize window
         */
        void unminimize();

        /**
         * Activates window
         */
        void activate();

    signals:

        void titleChanged(const QString &title);
        void iconNameChanged(const QString &title);

    protected:
        /**
         * Windows must be instantiated by a Task::Monitor, and are initially
         * owned only by the monitor. Connect to signals to receive events
         */
        explicit Window(WId id);

        /*
         * Friend accessors to set private internal bits
         */
        void setTitle(const QString &title);
        void setIconName(const QString &title);

    private:
        WId id;
        QString winTitle;
        QString winIcon;
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
