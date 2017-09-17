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

#include "menu-window.h"

#include <QDebug>
#include <QDir>
#include <QDirIterator>

namespace Panel
{
    MenuWindow::MenuWindow() : QWidget(nullptr)
    {
        // Won't need this till styling or popovers.
        // setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_X11DoNotAcceptFocus);
        setAttribute(Qt::WA_ShowWithoutActivating);
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        setFocusPolicy(Qt::NoFocus);

        // TODO: Allow resizable window, store that size.
        setFixedSize(420, 570);

        // HACK!
        move(0, 0);

        // TODO: Lazy initialise!
        // TODO: Also look at ~/.local/share/applications - make xdg lib expose this shit
        this->scanDirectory(QStringLiteral("/usr/share/applications"));
        this->scanDirectory(QStringLiteral("/usr/local/share/applications"));
    }

    void MenuWindow::toggleVisibility()
    {
        if (isVisible()) {
            hide();
        } else {
            show();
        }
    }

    void MenuWindow::scanDirectory(const QString &location)
    {
        QDir dir(location);
        if (!dir.exists()) {
            qDebug() << "Skipping non-existent directory: " << location;
            return;
        }

        QDirIterator iter(dir);
        while (iter.hasNext()) {
            QString item = iter.next();
            QString base = iter.fileName();
            if (base == "." || base == "..") {
                continue;
            }

            // Only want .desktop. :)
            if (!base.endsWith(".desktop")) {
                continue;
            }

            auto desktopFile = new Desktop::DesktopFile(iter.filePath());
            if (!desktopFile->isValid()) {
                qDebug() << "Skipping invalid desktop file: " << iter.filePath();
                delete desktopFile;
                continue;
            }

            // TODO: Set XDG properly from XDG_CURRENT_DESKTOP
            if (!desktopFile->canShowInDesktop(QStringLiteral("Budgie:GNOME"))) {
                delete desktopFile;
                continue;
            }

            // Stuff it in.
            qDebug() << "Inserted desktop file: " << iter.filePath();
            this->menuEntries[base] = QSharedPointer<Desktop::DesktopFile>(desktopFile);
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
