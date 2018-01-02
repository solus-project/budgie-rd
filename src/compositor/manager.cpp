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

#include "manager.h"

using namespace Budgie::Compositor;

Manager::Manager() : m_registry(new Compositor::Registry())
{
    m_rendererID = QStringLiteral("org.budgie-desktop.compositor.OpenGLRenderer");
}

bool Manager::init()
{
    m_registry->discover();

    // Ensure we have our main renderer first up
    if (!m_registry->hasRenderPlugin(m_rendererID)) {
        qWarning() << "Missing plugin for renderer: " << m_rendererID;
        return false;
    }

    return true;
}

bool Manager::start()
{
    qDebug() << "TODO: Populate outputs..";
    // Go ahead and construct our server
    auto renderer = m_registry->getRenderPlugin(m_rendererID);
    m_server.reset(new Compositor::Server(renderer.data()));

    return m_server->start();
}

void Manager::shutdown()
{
    qDebug() << "Closing compositor";
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
