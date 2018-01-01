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

#include <QSharedPointer>

#include "registry.h"
#include "session-module-interface.h"

namespace Budgie::Session
{
    /**
     * Extend the core PluginRegistry to add shell specific functionality
     */
    class Registry : public PluginRegistry
    {
        Q_OBJECT

    public:
        explicit Registry();

        /**
         * Get a service from our known service providers by the given
         * name.
         *
         * Implementations should ensure they check for nullptr here
         */
        QSharedPointer<SessionModuleInterface> getSessionModule(const QString &name);

        /**
         * Wrap hasPlugin to lookup the name with session/ prefix
         */
        bool hasSessionModule(const QString &name);

        /**
         * Unload a Session plugin
         */
        void unloadSessionModule(const QString &name);
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
