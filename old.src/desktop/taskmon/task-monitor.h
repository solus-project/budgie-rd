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

#include "window.h"

#include <KWindowSystem>
#include <QHash>
#include <QObject>
#include <QSharedPointer>

namespace Task
{
    class Monitor : public QObject
    {
        Q_OBJECT

    public:
        /**
         * Create a new monitor to track windows on the display
         */
        explicit Monitor();

        /**
         * Emit signals for all existing windows. Clients should ensure that
         * they reduce duplicates
         */
        void notifyAll();

    signals:

        /**
         * A window has been opened on screen
         */
        void windowOpened(Window *window);

        /**
         * A previously known window has been closed
         */
        void windowClosed(Window *window);

    private slots:
        void kwinWindowAdded(WId id);
        void kwinWindowChanged(WId id, NET::Properties props, NET::Properties2 props2);
        void kwinWindowRemoved(WId id);

    private:
        QHash<WId, QSharedPointer<Window>> windows;
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
