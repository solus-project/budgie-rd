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
    qDebug() << "Looking for: " << name;
    return nullptr;
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
