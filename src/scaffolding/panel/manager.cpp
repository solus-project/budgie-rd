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

#include "manager.h"

Budgie::PanelManager::PanelManager(Budgie::ShellInterface *interface, QObject *parent)
    : QObject(parent), m_shell(interface)
{
    m_dummyWindow.reset(new Budgie::PanelWindow(m_shell));
}

Budgie::PanelManager::~PanelManager()
{
}

void Budgie::PanelManager::showPanels()
{
    m_dummyWindow->show();
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
