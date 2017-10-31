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
    DesktopFile::DesktopFile() : IniFile(), m_valid(false)
    {
    }

    DesktopFile::DesktopFile(const QString &path)
        : IniFile(path), m_valid(false), m_path(path), m_autostartDelay(0), m_crashCount(0),
          m_crashCountSupported(false)
    {
        static const QString desktopHeader = QStringLiteral("Desktop Entry");
        QFileInfo inf(path);

        if (!inf.exists()) {
            return;
        }

        m_basename = inf.fileName();

        if (!hasSection(desktopHeader)) {
            return;
        }

        m_name = getString(desktopHeader, QStringLiteral("Name"));
        m_icon = getString(desktopHeader, QStringLiteral("Icon"));
        m_exec = getString(desktopHeader, QStringLiteral("Exec"));
        m_tryExec = getString(desktopHeader, QStringLiteral("TryExec"));
        m_onlyShowIn = getStringList(desktopHeader, QStringLiteral("OnlyShowIn"));
        m_noDisplay = getBool(desktopHeader, QStringLiteral("NoDisplay"), false);

        // Very much modelled after GNOME session startup pieces
        resolveAutostartConditions();

        /* Crash count support, to make kwin happy */;
        m_crashCountSupported =
            getBool(desktopHeader, QStringLiteral("X-Budgie-Support-Crash-Param"));

        if (m_name == "" || m_exec == "") {
            return;
        }

        if (!resolveExec(m_exec)) {
            if (!resolveExec(m_tryExec)) {
                return;
            }
        }

        m_valid = true;
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
                m_autostartDelay = getInt(desktopHeader, QStringLiteral("X-GNOME-Autostart-Delay"));
            }
        }
        m_autostartDelay = getInt(desktopHeader, QStringLiteral("X-Budgie-Autostart-Delay"));
        if (m_autostartDelay < 1) {
            m_autostartDelay = getInt(desktopHeader, QStringLiteral("X-GNOME-Autostart-Delay"));
        }

        if (desktopAutostartPhase == QStringLiteral("Initialization")) {
            m_autostartPhase = AutostartPhase::Initialization;
        } else if (desktopAutostartPhase == QStringLiteral("WindowManager")) {
            m_autostartPhase = AutostartPhase::WindowManager;
        } else if (desktopAutostartPhase == QStringLiteral("Shell")) {
            m_autostartPhase = AutostartPhase::Shell;
        } else if (desktopAutostartPhase == QStringLiteral("Panel")) {
            m_autostartPhase = AutostartPhase::Shell;
        } else {
            m_autostartPhase = AutostartPhase::Applications;
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
        m_mainExec = binary;
        m_args = splits;
        m_args.removeFirst();
        m_fullCommand = exec;
        return true;
    }

    bool DesktopFile::valid()
    {
        return m_valid;
    }

    const QString &DesktopFile::id()
    {
        return m_basename;
    }

    bool DesktopFile::canShowInDesktop(const QString &desktopName)
    {
        if (m_onlyShowIn.length() < 1) {
            return true;
        }

        // Split running desktop name on ":", replace ";" with ":" to ensure
        // we're comparing properly.
        QString compUp = ("" + desktopName).toUpper().replace(";", ":");
        auto runningDesktop = compUp.split(":");

        // If one of our OnlyShowIn fields appears the upper-case comparison
        // we'll immediately return true.
        for (auto &id : m_onlyShowIn) {
            if (runningDesktop.contains(id.toUpper())) {
                return true;
            }
        }

        return false;
    }

    AutostartPhase DesktopFile::autostartPhase()
    {
        return m_autostartPhase;
    }

    void DesktopFile::setAutostartPhase(AutostartPhase phase)
    {
        m_autostartPhase = phase;
    }

    int DesktopFile::autostartDelay()
    {
        return m_autostartDelay;
    }

    void DesktopFile::setAutostartDelay(int delay)
    {
        m_autostartDelay = delay;
    }

    bool DesktopFile::crashCountSupported()
    {
        return m_crashCountSupported;
    }

    int DesktopFile::crashCount()
    {
        return m_crashCount;
    }

    void DesktopFile::setCrashCount(int crashCount)
    {
        m_crashCount = crashCount;
    }

    QProcess *DesktopFile::launch(const QStringList &args)
    {
        QStringList realArgs;

        for (auto &tmp : m_args) {
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

        if (m_crashCountSupported && m_crashCount > 0) {
            realArgs << "--crashes" << QString::number(m_crashCount);
        }

        QProcess *ret = new QProcess(this);
        ret->setProgram(m_exec);
        ret->setArguments(realArgs);

        // TODO: Support all fields properly..
        qDebug() << "Command: " << m_exec << " " << realArgs;

        return ret;
    }

    const QString &DesktopFile::name()
    {
        return m_name;
    }

    QString DesktopFile::nameLocal()
    {
        static const QString desktopHeader = QStringLiteral("Desktop Entry");
        static const QString localeName = QLocale::system().name();
        static const QStringList localeSplit = localeName.split("_");

        auto lookup = getString(desktopHeader, QString("Name[" + localeName + "]"));
        if (!lookup.isEmpty()) {
            return lookup;
        }
        lookup = getString(desktopHeader, QString("Name[" + localeSplit[0] + "]"), "");
        if (!lookup.isEmpty()) {
            return lookup;
        }
        return m_name;
    }

    const QString &DesktopFile::iconName()
    {
        return m_icon;
    }

    QIcon DesktopFile::icon()
    {
        // TODO: Check if we actually have some kind of QPixmap ..
        if (m_icon.isEmpty()) {
            return QIcon::fromTheme("image-missing");
        }
        return QIcon::fromTheme(m_icon, QIcon::fromTheme("image-missing"));
    }

    bool DesktopFile::visible()
    {
        return !m_noDisplay;
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
