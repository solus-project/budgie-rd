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
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    // We must disable Qt's glib integration as we have no use for it, which
    // would leave to excessive wake ups
    qputenv("QT_NO_GLIB", "1");
    QString xdgDesktopName;

    // Before we do anything, ensure XDG_CURRENT_DESKTOP is sane.
    if (!qEnvironmentVariableIsEmpty("XDG_CURRENT_DESKTOP")) {
        xdgDesktopName = QString::fromLocal8Bit(qgetenv("XDG_CURRENT_DESKTOP"));
        if (xdgDesktopName != "Budgie") {
            qWarning() << "XDG_CURRENT_DESKTOP isn't set to Budgie";
        }
    } else {
        xdgDesktopName = "Budgie";
        qputenv("XDG_DESKTOP_NAME", xdgDesktopName.toLocal8Bit());
    }

    QGuiApplication::setFallbackSessionManagementEnabled(false);

    QCoreApplication::setApplicationName("budgie-rd-session");
    QCoreApplication::setApplicationVersion("0.0.0");

    Session::Manager manager(xdgDesktopName, argc, argv);
    return manager.exec();
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
