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
     * Plugins implementing FaceInterface are the primary visual entry point
     * nito the desktop and provide the main UI seen on screen.
     */
    class FaceInterface
    {
    public:
        virtual ~FaceInterface()
        {
        }

        /**
         * Ask the Face to initialise
         */
        virtual bool init() = 0;

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

Q_DECLARE_INTERFACE(Budgie::FaceInterface, "org.budgie-desktop.FaceInterface")

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
