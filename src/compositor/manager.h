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
#include <QSharedPointer>

namespace Budgie::Compositor
{
    /**
     * The Compositor::Manager is responsible for the main lifecycle of
     * our budgie-rd-compositor process, and is also responsible for loading
     * our main plugins that provide rendering, effects, etc.
     */
    class Manager : public QObject
    {
        Q_OBJECT

    public:
        explicit Manager();

        /**
         * Ensure we have a sane configuration and we're actually able to
         * perform a startup. Does not actually start any plugins.
         */
        bool init();

        /**
         * Start bringing the compositor itself up and activate the primary
         * rendering interface.
         */
        bool start();

    private:
        void shutdown();
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
