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
#include <QDirIterator>
#include <QFileInfo>

#include <pwd.h>
#include <unistd.h>

namespace Session
{
    /**
     * Quick C++ wrapper helper to really determine the home directory.
     * Typically we're expected to conform with `HOME` environment variable,
     * however we're the root level session, so we must ensure we're actually
     * trying to get the pw entry for the user before falling back to `HOME`.
     */
    static inline QString homeDirectory()
    {
        struct passwd *pw = nullptr;

        pw = getpwuid(getuid());
        if (!pw) {
            return QDir::homePath();
        }
        if (!pw->pw_dir) {
            return QDir::homePath();
        }
        return QString(pw->pw_dir);
    }

    Manager::Manager(const QString &xdgDesktopName, int &argc, char **argv)
        : QCoreApplication(argc, argv), xdgDesktopName(xdgDesktopName)
    {
        homeDir = homeDirectory();

        appendAutostartDirectory(homeDir + "/.config/autostart");

        // "Standard" (non-stateless) XDG location
        appendAutostartDirectory("/etc/xdg/autostart");

        // Locally installed global apps
        appendAutostartDirectory("/usr/local/share/autostart");

        // Currently specific to Solus & Clear Linux
        appendAutostartDirectory("/usr/share/xdg/autostart");

        scanAutostartApps();

        // Less .desktop files to scan if we have them in a dedicated directory,
        // unlike how gnome-session handled it. Additionally, we could support
        // multiple autostart profiles here.
        //
        // TODO: Pull our SHAREDIR from a global config.h
        scanSessionApps("/usr/share/budgie-session/desktop");

        // Fix the global process environment (QProcess) and remove any hacks
        // we've applied to it to not break any child processes
        execEnviron = QProcessEnvironment::systemEnvironment();
        execEnviron.remove(QStringLiteral("QT_NO_GLIB"));
    }

    void Manager::appendAutostartDirectory(const QString &directory)
    {
        QDir d(directory);
        if (!d.exists()) {
            qDebug() << "XDG: Skipping non-existent directory " << directory;
            return;
        }
        appDirs.append(d);
    }

    void Manager::scanAutostartApps()
    {
        for (auto &dir : appDirs) {
            QDirIterator iter(dir);
            while (iter.hasNext()) {
                QString item = iter.next();
                QString base = iter.fileName();
                if (base == "." || base == "..") {
                    continue;
                }
                // We're only interested in .desktop files here
                if (!base.endsWith(".desktop")) {
                    continue;
                }
                // We perform a descending insert, so don't allow overriding
                // an existing entry
                if (xdgAutostarts.contains(base)) {
                    continue;
                }
                const QFileInfo info = iter.fileInfo();
                // Forcibly disable it
                if (info.isSymLink() && info.symLinkTarget() == "/dev/null") {
                    xdgAutostarts.insert(base, QSharedPointer<DesktopFile>(new DesktopFile()));
                    continue;
                }
                if (!info.exists()) {
                    qDebug() << "Invalid .desktop file: " << item;
                    continue;
                }

                // Determine if the path is really valid ..
                auto desktopFile = new DesktopFile(iter.filePath());
                if (!desktopFile->isValid() || !desktopFile->canShowInDesktop(xdgDesktopName)) {
                    delete desktopFile;
                    continue;
                }

                xdgAutostarts.insert(base, QSharedPointer<DesktopFile>(desktopFile));
                qDebug() << "Inserting " << desktopFile->id();
            }
        }

        qDebug() << "No op";
    }

    void Manager::scanSessionApps(const QString &sessionDir)
    {
        QDir directory(sessionDir);
        QDirIterator iter(directory);

        while (iter.hasNext()) {
            QString item = iter.next();
            QString base = iter.fileName();
            if (base == "." || base == "..") {
                continue;
            }
            // We're only interested in .desktop files here
            if (!base.endsWith(".desktop")) {
                continue;
            }

            if (!iter.fileInfo().exists()) {
                qWarning() << "Skipping invalid .desktop file: " << iter.filePath();
                continue;
            }

            auto desktopFile = new DesktopFile(iter.filePath());
            if (!desktopFile->isValid() || !desktopFile->canShowInDesktop(xdgDesktopName)) {
                qWarning() << "Found .desktop file in session directory that isn't valid: "
                           << iter.filePath();
                delete desktopFile;
                continue;
            }

            qDebug() << "TODO: Insert autostart item: " << desktopFile->id() << " @ "
                     << desktopFile->autostartPhase();
        }
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
