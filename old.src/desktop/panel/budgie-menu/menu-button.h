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

#pragma once

// Fuckin seriously? Sort out cflags and expose xdg as a .so
#include "../../../xdg/desktop-file.h"

#include <QListWidgetItem>
#include <QObject>
#include <QSharedPointer>

namespace Panel
{
    class MenuButton : public QListWidgetItem
    {
    public:
        explicit MenuButton(Desktop::DesktopFile *file, QListWidget *parent = nullptr);

    private:
        QSharedPointer<Desktop::DesktopFile> desktopFile;
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
