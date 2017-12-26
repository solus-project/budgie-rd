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

// Fuckin seriously? Sort out cflags and expose xdg as a .so
#include "../../../xdg/desktop-file.h"
#include "menu-button.h"

#include <QHash>
#include <QListWidget>
#include <QSharedPointer>
#include <QWidget>

namespace Panel
{
    class MenuWindow : public QWidget
    {
        Q_OBJECT

    public:
        explicit MenuWindow();

        /**
         * Parent widget here refers to the button used to invoke
         * the action
         */
        void toggleVisibility(QWidget *parentWidget = nullptr);

    private:
        QHash<QString, QSharedPointer<MenuButton>> menuEntries;

        // TODO: Do this based on a list of XDG dirs
        void scanDirectory(const QString &location);

        QListWidget *rootList;
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
