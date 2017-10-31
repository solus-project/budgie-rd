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

#include <QIcon>
#include <QProcess>

#include "ini-parser.h"

namespace Desktop
{
    Q_NAMESPACE

    enum AutostartPhase {
        None = 0,
        Initialization,
        WindowManager,
        Shell, /** Panel */
        Applications,
    };

    Q_ENUM_NS(AutostartPhase)

    class DesktopFile : public IniFile
    {
        Q_OBJECT

    public:
        explicit DesktopFile();
        explicit DesktopFile(const QString &path);

        /**
         * Determine if the given .desktop file is actually valid
         */
        bool valid();

        /**
         * Return the ID for this desktop file, i.e. "gedit.desktop"
         */
        const QString &id();

        /**
         * Determine if the item is allowed to be shown in the current desktop
         * environment.
         */
        bool canShowInDesktop(const QString &desktopName);

        /**
         * Determine the AutostartPhase for the .desktop file.
         */
        AutostartPhase autostartPhase();

        /**
         * Override the internal autostart phase to prevent "special" autostart
         * directories doing what they shouldn't.
         */
        void setAutostartPhase(AutostartPhase phase);

        /**
         * Return the delay for starting the given autostart component
         */
        int autostartDelay();

        /**
         * Override (or set) the internal autostart delay
         */
        void setAutostartDelay(int delay);

        /**
         * The .desktop file supports having its application invoked with `--crashes <N>`
         * parameter, i.e. like kwin_x11
         */
        bool crashCountSupported();

        /**
         * Set the crash count to be passed to the application
         */
        void setCrashCount(int crashCount);

        /**
         * Return the current crash count for this .desktop file
         */
        int crashCount();

        /**
         * Attempt to launch the process with the given arguments. Internally
         * we will substitute any relevant arguments before passing them to
         * the application to be launched.
         *
         * This process will not initially be started, and will be parented
         * to this DesktopFile instance. It is up to the caller to override
         * the execution environment before starting the process.
         */
        QProcess *launch(const QStringList &args = QStringList());

        /**
         * Return the name in the .desktop file
         */
        const QString &name();

        /**
         * Return the icon field of the .desktop file.
         */
        const QString &iconName();

        /**
         * Return a QIcon resource for the .desktop file, using fallbacks
         * where appropriate.
         */
        QIcon icon();

        /**
         * Determine whether this .desktop file is meant to be displayed graphically
         */
        bool visible();

    private:
        bool m_valid;
        QString m_path;
        QString m_id;
        QString m_exec;
        QString m_tryExec;
        QString m_name;
        QString m_icon;
        QStringList m_onlyShowIn;
        QString m_executable;
        QString m_fullCommand;
        QString m_basename;
        AutostartPhase m_autostartPhase;
        int m_autostartDelay;
        int m_crashCount;
        bool m_crashCountSupported;
        bool m_noDisplay;
        QString m_mainExec;
        QStringList m_args;

        bool resolveExec(const QString &exec);
        void resolveAutostartConditions();
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
