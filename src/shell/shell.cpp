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
    : m_registry(new PluginRegistry()), m_sessionName(name),
      m_faceName("org.budgie-desktop.faces.Default"),
      m_essentialServices({ "org.budgie-desktop.services.WindowManager" }),
      m_standardServices({ "org.budgie-desktop.services.Notifications" })
{
}

const QString &Budgie::Shell::sessionName()
{
    return m_sessionName;
}

bool Budgie::Shell::init()
{
    // Discover all services
    m_registry->discover();

    // Make sure essential plugins are present
    auto serviceSet = m_essentialServices + m_standardServices;
    for (const auto &id : serviceSet) {
        if (!m_registry->hasServicePlugin(id)) {
            qWarning() << "Missing service plugin: " << id;
            return false;
        }
        auto service = m_registry->getService(id);
        if (service.isNull()) {
            qWarning() << "Failed to load service: " << id;
            return false;
        }
        if (!service->init(this)) {
            qWarning() << "Cannot init plugin: " << id;
            return false;
        }
    }

    // We need our face
    if (!m_registry->hasFacePlugin(m_faceName)) {
        qWarning() << "Missing face plugin: " << m_faceName;
        return false;
    }

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

bool Budgie::Shell::startFace()
{
    auto face = m_registry->getFace(m_faceName);
    if (face.isNull()) {
        qWarning() << "Failed to load face:" << m_faceName;
        return false;
    }

    // Init plugin
    if (!face->init(this)) {
        qWarning() << "Failed to init face:" << m_faceName;
        return false;
    }

    // Get it on screen
    if (!face->show()) {
        qWarning() << "Failed to set face to show:" << m_faceName;
        return false;
    }

    // We're now on screen apparently.
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
