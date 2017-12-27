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
    qDebug() << "Looking for: " << lookup;
    return nullptr;
}

/**
 * Attempt to load a service plugin with the given name
 */
bool Budgie::PluginRegistry::loadServicePlugin(const QString &name)
{
    QDir serviceDir(m_systemDirectory.filePath("services"));
    QString lookup("services/" + name);

    // Sure, whatever. We already loaded it. :P
    if (m_plugins.contains(lookup)) {
        return true;
    }

    // TODO: Make this portable and not janky.
    QString libName("lib" + name + ".so");
    QString fullPath = serviceDir.filePath(libName);

    Budgie::Plugin *plugin = Budgie::Plugin::newFromFilename(fullPath);

    if (!plugin) {
        return false;
    }

    // Now make this plugin instance owned
    qDebug() << "Loaded " << lookup;
    m_plugins.insert(lookup, QSharedPointer<Budgie::Plugin>(plugin));
    return true;
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
