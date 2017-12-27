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

namespace Budgie
{
    /**
     * The PanelInterface is the abstract API with which to interact with
     * a panel object.
     */
    class PanelInterface
    {
    public:
        virtual ~PanelInterface()
        {
        }

        /**
         * Request the panel show itself
         */
        virtual void show() = 0;

        /**
         * Request the panel hide itself
         */
        virtual void hide() = 0;
    };
}

Q_DECLARE_INTERFACE(Budgie::PanelInterface, "org.budgie-desktop.PanelInterface")

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
