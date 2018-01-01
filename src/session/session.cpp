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

#include <QCoreApplication>
#include <QDebug>

#include "session.h"

Budgie::Session::Session(const QString &name)
    : m_sessionName(name), m_registry(new SessionRegistry())
{
    // Start window manager first, very important. :P
    m_requiredServices << "org.budgie-desktop.session.WindowManager";

    // Get the shell up and running next
    m_requiredServices << "org.budgie-desktop.session.Shell";
}

const QString &Budgie::Session::sessionName()
{
    return m_sessionName;
}

bool Budgie::Session::init()
{
    // Discover all modules
    m_registry->discover();

    for (const auto &serviceID : m_requiredServices) {
        if (!m_registry->hasSessionModule(serviceID)) {
            qWarning() << "Missing session module: " << serviceID;
            return false;
        }
    }

    return true;
}

bool Budgie::Session::start()
{
    for (const auto &serviceID : m_requiredServices) {
        auto service = m_registry->getSessionModule(serviceID);
        qDebug() << "Starting session module: " << serviceID;
        if (!service->start()) {
            qWarning() << "Failed to start session module: " << serviceID;
            shutdownSession();
            return false;
        }
        m_activeServices << serviceID;
    }

    return true;
}

void Budgie::Session::shutdownSession()
{
    std::reverse(std::begin(m_activeServices), std::end(m_activeServices));

    for (const auto &id : m_activeServices) {
        auto service = m_registry->getSessionModule(id);
        if (!service) {
            qWarning() << "Error in accounting: " << id << " is not accounted for";
            continue;
        }
        qDebug() << "Stopping shell module: " << id;
        service->stop();
    }

    qDebug() << "Closing Session";
    QCoreApplication::quit();
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
