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

#include <QDebug>
#include <QFileInfo>
#include <QStandardPaths>

namespace Session
{
    DesktopFile::DesktopFile() : QSettings(), valid(false)
    {
    }

    DesktopFile::DesktopFile(const QString &path)
        : QSettings(path, QSettings::IniFormat), valid(false), path(path), desktopAutostartDelay(0),
          desktopCrashCount(0), desktopSupportCrashCount(false)
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
        desktopExec = value("Exec", "").toString().trimmed();
        desktopTryExec = value("TryExec", "").toString().trimmed();
        desktopOnlyShowIn = value("OnlyShowIn", "").toString().trimmed();

        // Very much modelled after GNOME session startup pieces
        QString desktopAutostartPhase = value("X-Budgie-Autostart-Phase", "").toString().trimmed();
        desktopAutostartDelay = value("X-Budgie-Autostart-Delay", 0).toInt();

        /* Crash count support, to make kwin happy */;
        this->desktopSupportCrashCount = value("X-Budgie-Support-Crash-Param").toBool();

        endGroup();

        if (desktopAutostartPhase == QStringLiteral("Initialization")) {
            this->desktopAutostartPhase = AutostartPhase::Initialization;
        } else if (desktopAutostartPhase == QStringLiteral("WindowManager")) {
            this->desktopAutostartPhase = AutostartPhase::WindowManager;
        } else if (desktopAutostartPhase == QStringLiteral("Shell")) {
            this->desktopAutostartPhase = AutostartPhase::Shell;
        } else {
            this->desktopAutostartPhase = AutostartPhase::Applications;
        }

        if (status() != QSettings::NoError) {
            return;
        }

        if (desktopName == "" || desktopExec == "") {
            return;
        }

        if (!resolveExec(desktopExec) && !resolveExec(desktopTryExec)) {
            return;
        }

        valid = true;
    }

    bool DesktopFile::resolveExec(const QString &exec)
    {
        auto splits = exec.split(" ");
        QString binary = splits[0];
        if (!binary.startsWith("/")) {
            binary = QStandardPaths::findExecutable(binary);
        }
        if (binary.isEmpty()) {
            return false;
        }
        QFileInfo e(binary);
        if (!e.exists() || !e.isExecutable()) {
            return false;
        }
        this->mainExec = binary;
        this->mainArgs = splits;
        this->mainArgs.removeFirst();
        this->desktopFullCommand = exec;
        return true;
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

    AutostartPhase DesktopFile::autostartPhase()
    {
        return this->desktopAutostartPhase;
    }

    void DesktopFile::setAutostartPhase(AutostartPhase phase)
    {
        this->desktopAutostartPhase = phase;
    }

    int DesktopFile::autostartDelay()
    {
        return this->desktopAutostartDelay;
    }

    void DesktopFile::setAutostartDelay(int delay)
    {
        this->desktopAutostartDelay = delay;
    }

    bool DesktopFile::supportCrashCount()
    {
        return this->desktopSupportCrashCount;
    }

    int DesktopFile::crashCount()
    {
        return this->desktopCrashCount;
    }

    void DesktopFile::setCrashCount(int crashCount)
    {
        this->desktopCrashCount = crashCount;
    }

    QProcess *DesktopFile::launch(const QStringList &args)
    {
        QStringList realArgs;
        for (auto &tmp : this->mainArgs) {
            if (tmp.contains("%f")) {
                tmp.replace("%f", args[0]);
            }
            if (tmp.contains("%F")) {
                tmp.replace("%F", args.join(" "));
            }
            if (tmp.contains("%u")) {
                if (args[0].contains(":/")) {
                    tmp.replace("%u", args[0]);
                } else {
                    tmp.replace("%u", "file://" + args[0]);
                }
            }
            if (tmp.contains("%U")) {
                QStringList tmpArgs;
                for (const auto &arg : args) {
                    if (arg.contains(":/")) {
                        tmpArgs << arg;
                    } else {
                        tmpArgs << "file://" + arg;
                    }
                }
                tmp.replace("%U", tmpArgs.join(" "));
            }
            realArgs << tmp;
        }

        if (desktopSupportCrashCount && desktopCrashCount > 0) {
            realArgs << "--crashes" << QString::number(desktopCrashCount);
        }
    done:
        // TODO: Support all fields properly..
        qDebug() << "Command: " << mainExec << " " << realArgs;
        return nullptr;
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
