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

#include <QDir>
#include <QHash>
#include <QObject>
#include <QSharedPointer>

#include "face-interface.h"
#include "plugin.h"
#include "service-interface.h"

namespace Budgie
{
    /**
     * The PluginRegistry is used to locate plugins by capability and load
     * them to construct a dynamic desktop environment.
     */
    class PluginRegistry : public QObject
    {
        Q_OBJECT

        friend class Shell;

    public:
        explicit PluginRegistry();

        /**
         * Return a Plugin instance with the given absolute name.
         * Callers should ensure to prefix with the right type or
         * use the accessor functions.
         */
        template <class T> QSharedPointer<T> getPlugin(const QString &name);

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
         * Determine if we have the given plugin or not
         */
        bool hasPlugin(const QString &name);

        /**
         * Wrap hasPlugin to lookup the name with services/ prefix
         */
        bool hasServicePlugin(const QString &name);

        /**
         * Wrap hasPlugin to lookup the name with the faces/ prefix
         */
        bool hasFacePlugin(const QString &name);

        /**
         * Unload a named plugin
         */
        void unload(const QString &name);

        /**
         * Unload a Face plugin
         */
        void unloadFace(const QString &name);

        /**
         * Unload a Service plugin
         */
        void unloadService(const QString &name);

    protected:
        void discover();
        void discoverType(const QString &type);

    private:
        QDir m_systemDirectory;
        QHash<QString, QSharedPointer<Plugin>> m_plugins;
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
