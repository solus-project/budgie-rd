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

#include "face-interface.h"
#include "registry.h"
#include "service-interface.h"

namespace Budgie::Shell
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
        QSharedPointer<ServiceInterface> getService(const QString &name);

        /**
         * Get a face from our known face providers by the given
         * name.
         *
         * Implementations should ensure they check for nullptr here
         */
        QSharedPointer<FaceInterface> getFace(const QString &name);

        /**
         * Wrap hasPlugin to lookup the name with services/ prefix
         */
        bool hasServicePlugin(const QString &name);

        /**
         * Wrap hasPlugin to lookup the name with the faces/ prefix
         */
        bool hasFacePlugin(const QString &name);

        /**
         * Unload a Face plugin
         */
        void unloadFace(const QString &name);

        /**
         * Unload a Service plugin
         */
        void unloadService(const QString &name);
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
