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

#include <QDebug>

#include "face.h"

bool Budgie::DefaultFace::init(Budgie::ShellInterface *interface)
{
    m_shell = interface;
    qDebug() << "Init DefaultFace";

    // Ensure we can own the PanelManager interface
    m_panelManager = new Budgie::Panel::Manager(m_shell, this);
    if (!m_shell->registerInterface(m_panelManager)) {
        qWarning() << "Failed to register the panel manager. Aborting";
        return false;
    }

    m_raven.reset(new Budgie::Raven::Window(m_shell));
    if (!m_shell->registerInterface(m_raven.data())) {
        qWarning() << "Failed to register the Raven widget. Aborting";
        return false;
    }

    return true;
}

bool Budgie::DefaultFace::show()
{
    qDebug() << "Showing DefaultFace";

    m_panelManager->showPanels();
    return true;
}

void Budgie::DefaultFace::shutdown()
{
    qDebug() << "Teardown DefaultFace";
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
