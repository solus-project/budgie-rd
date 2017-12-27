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

#include <QDebug>
#include <QDirIterator>

#include "config.h"
#include "registry.h"

Budgie::PluginRegistry::PluginRegistry()
{
    // Set up our default loader paths
    m_systemDirectory = QStringLiteral(BUDGIE_PLUGIN_DIRECTORY);
    qDebug() << "Set system directory to: " << m_systemDirectory.path();
}

QSharedPointer<Budgie::ServiceInterface> Budgie::PluginRegistry::getService(const QString &name)
{
    QString lookup("services/" + name);
    QSharedPointer<Budgie::Plugin> plugin = m_plugins.value(lookup, nullptr);
    if (plugin.isNull()) {
        qDebug() << "Unknown plugin: " << name;
        return nullptr;
    }

    return QSharedPointer<Budgie::ServiceInterface>(
        qobject_cast<Budgie::ServiceInterface *>(plugin->instance()));
}

bool Budgie::PluginRegistry::hasPlugin(const QString &name)
{
    return m_plugins.contains(name);
}

bool Budgie::PluginRegistry::hasServicePlugin(const QString &name)
{
    return m_plugins.contains(QStringLiteral("services/") + name);
}

void Budgie::PluginRegistry::discoverType(const QString &type)
{
    QDir serviceDir(m_systemDirectory.filePath(type));
    QDirIterator it(serviceDir, QDirIterator::NoIteratorFlags);
    while (it.hasNext()) {
        QFileInfo info(it.next());
        Budgie::Plugin *plugin = nullptr;

        if (!info.isFile()) {
            continue;
        }
        if (!info.fileName().endsWith(QStringLiteral(".so"))) {
            continue;
        }

        plugin = Budgie::Plugin::newFromFilename(info.filePath());
        if (!plugin) {
            qDebug() << "Invalid plugin: " << info.filePath();
            continue;
        }

        QString fullID(type + "/" + plugin->name());
        if (m_plugins.contains(fullID)) {
            qDebug() << "Not replacing " << type << " plugin" << fullID << "with "
                     << info.fileName();
            delete plugin;
            continue;
        }

        m_plugins.insert(fullID, QSharedPointer<Budgie::Plugin>(plugin));
        qDebug() << "New " << type << " plugin: " << fullID << "(" << info.filePath() << ")";
    }
}

/**
 * Discover all available plugins and store them by their identifiers
 */
void Budgie::PluginRegistry::discover()
{
    discoverType("services");
    discoverType("faces");
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
