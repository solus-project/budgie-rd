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

#include <QObject>
#include <QSharedPointer>

#include "session-registry.h"

namespace Budgie
{
    /**
     * The Budgie::Session is the main entry into the Budgie Desktop, and
     * uses modules to construct an appropriate session to support the
     * primary shell and userland applications.
     */
    class Session : public QObject
    {
        Q_OBJECT

    public:
        explicit Session(const QString &name);

        /**
         * Return the session name that we will be using, to permit fallback
         * paths for failed session starts.
         */
        const QString &sessionName();

        /**
         * Ensure we have a sane configuration and we're actually able to
         * perform a startup. Does not actually start any services
         */
        bool init();

        /**
         * Once the main event loop is rolling, start bringing up support
         * services in the session, including the main shell itself.
         */
        bool start();

    private:
        QString m_sessionName;
        QStringList m_requiredServices;
        QStringList m_activeServices;
        QSharedPointer<SessionRegistry> m_registry;

        void shutdownSession();
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
