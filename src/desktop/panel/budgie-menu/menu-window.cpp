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
#include <QPushButton>
#include <QVBoxLayout>

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

        auto layout = new QVBoxLayout();
        layout->setMargin(0);
        setLayout(layout);

        rootList = new QListWidget(this);
        layout->addWidget(rootList);

        auto button = new QPushButton(QStringLiteral("Log out kthxbai"), this);
        button->setIcon(QIcon::fromTheme("system-log-out"));
        layout->addWidget(button);

        // TODO: Allow resizable window, store that size.
        setFixedSize(420, 570);

        // HACK!
        move(0, 0);

        // TODO: Lazy initialise!
        // TODO: Also look at ~/.local/share/applications - make xdg lib expose this shit
        this->scanDirectory(QStringLiteral("/usr/share/applications"));
        this->scanDirectory(QStringLiteral("/usr/local/share/applications"));
    }

    void MenuWindow::toggleVisibility(QWidget *parentWidget)
    {
        if (isVisible()) {
            hide();
            return;
        }
        if (!parentWidget) {
            show();
            return;
        }
        auto rect = parentWidget->geometry();
        QPoint abs = parentWidget->mapToGlobal(QPoint(rect.x(), rect.y()));

        // Hack, we'll just show above the widget for now.
        auto x = abs.x();
        auto y = abs.y() - height();
        move(x, y);
        show();
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
            if (!desktopFile->visible() ||
                !desktopFile->canShowInDesktop(QStringLiteral("Budgie:GNOME"))) {
                delete desktopFile;
                continue;
            }

            // TODO: Stick it in the UI with proper layout ...
            auto button = new MenuButton(desktopFile, this->rootList);

            // Stuff it in.
            qDebug() << "Inserted desktop file: " << iter.filePath();
            menuEntries.insert(base, QSharedPointer<MenuButton>(button));
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
