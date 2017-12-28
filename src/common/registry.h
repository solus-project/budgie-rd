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

    public:
        explicit PluginRegistry();

        /**
         * Return a Plugin instance with the given absolute name.
         * Callers should ensure to prefix with the right type or
         * use the accessor functions.
         */
        template <class T> QSharedPointer<T> getPlugin(const QString &name)
        {
            QSharedPointer<Plugin> plugin = m_plugins.value(name, nullptr);
            if (plugin.isNull()) {
                return nullptr;
            }
            return qSharedPointerDynamicCast<T>(plugin->instance());
        }

        /**
         * Determine if we have the given plugin or not
         */
        bool hasPlugin(const QString &name);

        /**
         * Unload a named plugin
         */
        void unload(const QString &name);

        /**
         * Discover all possible plugins
         */
        void discover();

        /**
         * Append a new directory to the search path
         */
        void appendSearchPath(const QString &searchDir);

        /**
         * Return the root to the system directory for plugins
         */
        const QDir &systemDirectory();

    private:
        QDir m_systemDirectory;
        QStringList m_searchPaths;

        QHash<QString, QSharedPointer<Plugin>> m_plugins;
        void discoverDir(const QDir &rootDir);
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
