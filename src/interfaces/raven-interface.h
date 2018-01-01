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

#define BudgieRavenInterfaceIID "org.budgie-desktop.RavenInterface"

namespace Budgie
{
    /**
     * The RavenInterface is the abstract API with which to interact with
     * a panel object.
     */
    class RavenInterface : public BaseInterface
    {
    public:
        virtual ~RavenInterface()
        {
        }

        inline const QString interfaceName() override
        {
            return QStringLiteral(BudgieRavenInterfaceIID);
        }

        /**
         * Request the Raven instance open to the default view
         */
        virtual void show() = 0;

        /**
         * Explicitly hide the Raven instance if open
         */
        virtual void hide() = 0;

        /**
         * If Raven is visible, hide it, otherwise, show it.
         */
        virtual void toggle() = 0;
    };
}

Q_DECLARE_INTERFACE(Budgie::RavenInterface, BudgieRavenInterfaceIID)

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
