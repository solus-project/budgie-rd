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

Budgie::Shell::Shell(const QString &name) : m_essentialServices({ "windowmanager" })
{
    m_name = name;
    m_registry.reset(new PluginRegistry());

    // This is a bit unrealistic but in future we'll take the service plugin
    // list from some definition file.
    m_standardServices << "notifications";
}

const QString &Budgie::Shell::name()
{
    return m_name;
}

bool Budgie::Shell::init()
{
    // Lets pretend we error check
    return true;
}

bool Budgie::Shell::startEssential()
{
    // We must be able to start all of our required service IDs otherwise
    // we've failed completely.
    return startServiceSet(m_essentialServices, true);
}

bool Budgie::Shell::startRemaining()
{
    // Not so fatal.
    return startServiceSet(m_standardServices, false);
}

bool Budgie::Shell::startServiceSet(const QStringList &serviceIDs, bool fatal)
{
    for (const auto &serviceID : serviceIDs) {
        auto service = m_registry->getService(serviceID);
        if (service.isNull()) {
            qWarning() << "Failed to load service: " << serviceID;
            if (fatal) {
                return false;
            }
            continue;
        }

        qDebug() << "Starting service: " << serviceID;
        if (!service->start()) {
            qWarning() << "Failed to start service: " << serviceID;
            if (fatal) {
                return false;
            }
            continue;
        }
    }

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
