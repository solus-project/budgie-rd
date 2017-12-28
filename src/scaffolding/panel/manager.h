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

#pragma once

#include <QObject>
#include <QScopedPointer>
#include <QWidget>

#include "panel-manager-interface.h"
#include "shell-interface.h"
#include "window.h"

namespace Budgie
{
    /**
     * A concrete implementation of the PanelManager using QtWidget based
     * Panels
     */
    class PanelManager : public QObject, public PanelManagerInterface
    {
        Q_OBJECT

    public:
        explicit PanelManager(ShellInterface *interface, QObject *parent = nullptr);
        ~PanelManager();

        /* We have go ahead to show content on screen now */
        void showPanels();

    private:
        QScopedPointer<PanelWindow> m_dummyWindow;
        ShellInterface *m_shell;
    };
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
