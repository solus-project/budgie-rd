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

#include "desktop-file.h"

#include <QFileInfo>

namespace Session
{
    DesktopFile::DesktopFile() : QSettings(), valid(false)
    {
    }

    DesktopFile::DesktopFile(const QString &path)
        : QSettings(path, QSettings::IniFormat), valid(false), path(path)
    {
        QFileInfo inf(path);
        if (!inf.exists()) {
            return;
        }

        basename = inf.fileName();

        if (!childGroups().contains("Desktop Entry")) {
            return;
        }

        beginGroup("Desktop Entry");
        desktopName = value("Name", "").toString().trimmed();
        desktopExec = value("Exec", "").toString().trimmed().split(" ")[0];
        desktopTryExec = value("TryExec", "").toString().trimmed().split(" ")[0];
        desktopOnlyShowIn = value("OnlyShowIn", "").toString().trimmed();
        endGroup();

        if (status() != QSettings::NoError) {
            return;
        }

        if (desktopName == "" || desktopExec == "") {
            return;
        }

        // Ensure we have a valid executable here
        QFileInfo mainExec(desktopExec);
        QFileInfo tryExec(desktopTryExec);

        if (!mainExec.exists() || !mainExec.isExecutable()) {
            if (tryExec.exists() && tryExec.isExecutable()) {
                desktopExecutable = desktopTryExec;
            } else {
                return;
            }
        } else {
            desktopExecutable = desktopExec;
        }

        valid = true;
    }

    bool DesktopFile::isValid()
    {
        return this->valid;
    }

    const QString &DesktopFile::id()
    {
        return this->basename;
    }

    bool DesktopFile::canShowInDesktop(const QString &desktopName)
    {
        if (this->desktopOnlyShowIn == "") {
            return true;
        }
        QString compUp = ("" + desktopName).toUpper().replace(";", ":");
        QString compUs = ("" + desktopOnlyShowIn).toUpper().replace(";", ":");

        auto splitsLeft = compUp.split(":");
        auto splitsRight = compUs.split(":");

        for (auto &id : splitsLeft) {
            if (splitsRight.contains(id)) {
                return true;
            }
        }

        return false;
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
