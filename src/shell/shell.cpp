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

#include "shell.h"

Budgie::Shell::Shell(const QString &name)
{
    m_name = name;
    m_registry.reset(new PluginRegistry());
}

const QString &Budgie::Shell::name()
{
    return m_name;
}

bool Budgie::Shell::start()
{
    auto service = m_registry->getService("notifications");
    if (service.isNull()) {
        qWarning() << "Failed to load notifications";
        return false;
    }
    qDebug() << "Starting notifications...";
    return service->start();
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
