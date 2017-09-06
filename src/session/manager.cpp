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

#include <QDebug>
#include <QDir>
#include <QFileInfo>

namespace Session
{
    Manager::Manager(int &argc, char **argv) : QCoreApplication(argc, argv)
    {
        // TODO: Replace with non shitty functions
        auto homedir = QDir::homePath();

        appendAutostartDirectory(homedir + "/.config");

        // "Standard" (non-stateless) XDG location
        appendAutostartDirectory("/etc/xdg/autostart");

        // Currently specific to Solus & Clear Linux
        appendAutostartDirectory("/usr/share/xdg/autostart");
    }

    void Manager::appendAutostartDirectory(const QString &directory)
    {
        QDir d(directory);
        if (!d.exists()) {
            qDebug() << "XDG: Skipping " << directory;
            return;
        }
        appDirs.append(d.absolutePath());
    }
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
