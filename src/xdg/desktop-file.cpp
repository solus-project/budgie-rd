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
#include <QString>

namespace Desktop
{
    DesktopFile::DesktopFile() : IniFile(), valid(false)
    {
    }

    DesktopFile::DesktopFile(const QString &path)
        : IniFile(path), valid(false), path(path), desktopAutostartDelay(0), desktopCrashCount(0),
          desktopSupportCrashCount(false)
    {
        static const QString desktopHeader = QStringLiteral("Desktop Entry");

        if (!hasSection(desktopHeader)) {
            return;
        }

        desktopName = getString(desktopHeader, QStringLiteral("Name"));
        desktopIcon = getString(desktopHeader, QStringLiteral("Icon"));
        desktopExec = getString(desktopHeader, QStringLiteral("Exec"));
        desktopTryExec = getString(desktopHeader, QStringLiteral("TryExec"));
        desktopOnlyShowIn = getStringList(desktopHeader, QStringLiteral("OnlyShowIn"));
        desktopNoDisplay = getBool(desktopHeader, QStringLiteral("NoDisplay"), false);

        // Very much modelled after GNOME session startup pieces
        resolveAutostartConditions();

        /* Crash count support, to make kwin happy */;
        this->desktopSupportCrashCount =
            getBool(desktopHeader, QStringLiteral("X-Budgie-Support-Crash-Param"), false);

        if (desktopName == "" || desktopExec == "") {
            return;
        }

        if (!resolveExec(desktopExec)) {
            if (!resolveExec(desktopTryExec)) {
                return;
            }
        }

        valid = true;
    }

    /**
     * Attempt to find the matching autostart conditions. For compatibility with
     * generic autostart files (such as pulseaudio's start-pulseaudio-x11) we also
     * resolve the X-GNOME condition, which would only be evaluated if the .desktop
     * file isValid(), i.e. the OnlyShowIn is correct.
     */
    void DesktopFile::resolveAutostartConditions()
    {
        static const QString desktopHeader = QStringLiteral("Desktop Entry");

        QString desktopAutostartPhase =
            getString(desktopHeader, QStringLiteral("X-Budgie-Autostart-Phase"));
        if (desktopAutostartPhase.isEmpty()) {
            desktopAutostartPhase =
                getString(desktopHeader, QStringLiteral("X-GNOME-Autostart-Phase"));
            if (!desktopAutostartPhase.isEmpty()) {
                desktopAutostartDelay =
                    getInt(desktopHeader, QStringLiteral("X-GNOME-Autostart-Delay"));
            }
        }
        desktopAutostartDelay = getInt(desktopHeader, QStringLiteral("X-Budgie-Autostart-Delay"));
        if (desktopAutostartDelay < 1) {
            desktopAutostartDelay =
                getInt(desktopHeader, QStringLiteral("X-GNOME-Autostart-Delay"));
        }

        if (desktopAutostartPhase == QStringLiteral("Initialization")) {
            this->desktopAutostartPhase = AutostartPhase::Initialization;
        } else if (desktopAutostartPhase == QStringLiteral("WindowManager")) {
            this->desktopAutostartPhase = AutostartPhase::WindowManager;
        } else if (desktopAutostartPhase == QStringLiteral("Shell")) {
            this->desktopAutostartPhase = AutostartPhase::Shell;
        } else if (desktopAutostartPhase == QStringLiteral("Panel")) {
            this->desktopAutostartPhase = AutostartPhase::Shell;
        } else {
            this->desktopAutostartPhase = AutostartPhase::Applications;
        }
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
        if (this->desktopOnlyShowIn.length() < 1) {
            return true;
        }

        // Split running desktop name on ":", replace ";" with ":" to ensure
        // we're comparing properly.
        QString compUp = ("" + desktopName).toUpper().replace(";", ":");
        auto runningDesktop = compUp.split(":");

        // If one of our OnlyShowIn fields appears the upper-case comparison
        // we'll immediately return true.
        for (auto &id : this->desktopOnlyShowIn) {
            if (runningDesktop.contains(id.toUpper())) {
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

        QProcess *ret = new QProcess(this);
        ret->setProgram(mainExec);
        ret->setArguments(realArgs);

        // TODO: Support all fields properly..
        qDebug() << "Command: " << mainExec << " " << realArgs;

        return ret;
    }

    const QString &DesktopFile::name()
    {
        return this->desktopName;
    }

    const QString &DesktopFile::iconName()
    {
        return this->desktopIcon;
    }

    QIcon DesktopFile::icon()
    {
        // TODO: Check if we actually have some kind of QPixmap ..
        if (this->desktopIcon.isEmpty()) {
            return QIcon::fromTheme("image-missing");
        }
        return QIcon::fromTheme(this->desktopIcon, QIcon::fromTheme("image-missing"));
    }

    bool DesktopFile::visible()
    {
        return !this->desktopNoDisplay;
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
