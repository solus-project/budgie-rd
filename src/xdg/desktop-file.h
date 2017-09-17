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

#include <QIcon>
#include <QProcess>
#include <QSettings>

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

    class DesktopFile : public QSettings
    {
        Q_OBJECT

    public:
        explicit DesktopFile();
        explicit DesktopFile(const QString &path);

        /**
         * Determine if the given .desktop file is actually valid
         */
        bool isValid();

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
        bool supportCrashCount();

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

    private:
        bool valid;
        QString path;
        QString desktopID;
        QString desktopExec;
        QString desktopTryExec;
        QString desktopName;
        QString desktopIcon;
        QString desktopOnlyShowIn;
        QString desktopExecutable;
        QString desktopFullCommand;
        QString basename;
        AutostartPhase desktopAutostartPhase;
        int desktopAutostartDelay;
        int desktopCrashCount;
        bool desktopSupportCrashCount;
        QString mainExec;
        QStringList mainArgs;

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
