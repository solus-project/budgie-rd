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

#include "base-interface.h"

#define BudgieSessionModuleInterfaceIID "org.budgie-desktop.SessionModuleInterface"

namespace Budgie
{
    /**
     * The SessionModuleInterface is used by the Budgie Session to provide
     * support services to the primary session binary.
     *
     * Unlike the ServiceInterface, a SessionModuleInterface implementation
     * cannot register arbitrary objects through a Shell broker. This is due
     * to the multiprocess nature of the session + shell. The session
     * modules should instead support bootstrapping the session environment
     * with additional services required **by** the shell.
     *
     * If a service is exposed in the session via this interface, i.e. as
     * a form of dbus service, then the corresponding ServiceInterface should
     * be implemented within the shell to proxy requests and make it accessible
     * to all plugins there.
     */
    class SessionModuleInterface : BaseInterface
    {
    public:
        virtual ~SessionModuleInterface()
        {
        }

        inline const QString interfaceName() override
        {
            return QStringLiteral(BudgieSessionModuleInterfaceIID);
        }

        /**
         * Ask the service interface to start itself
         */
        virtual bool start() = 0;

        /**
         * Ask the service interface to stop itself.
         */
        virtual bool stop() = 0;
    };
}

Q_DECLARE_INTERFACE(Budgie::SessionModuleInterface, BudgieSessionModuleInterfaceIID)

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
