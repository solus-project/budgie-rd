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

#include "base-interface.h"
#include "shell-interface.h"

namespace Budgie
{
    /**
     * Plugins implementing FaceInterface are the primary visual entry point
     * nito the desktop and provide the main UI seen on screen.
     */
    class FaceInterface : public BaseInterface
    {
    public:
        virtual ~FaceInterface()
        {
        }

        /**
         * Ask the Face to initialise
         */
        virtual bool init(const ShellInterface *shell) = 0;

        /**
         * Ask the Face to now make itself visible
         */
        virtual bool show() = 0;

        /**
         * Ask the Face implementation to tear itself down
         */
        virtual void shutdown() = 0;
    };
}

#define BudgieFaceInterfaceIID "org.budgie-desktop.FaceInterface"

Q_DECLARE_INTERFACE(Budgie::FaceInterface, BudgieFaceInterfaceIID)

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
