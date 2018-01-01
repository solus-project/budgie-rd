/*
 * This file is part of budgie-rd
 *
 * Copyright © 2017-2018 Budgie Desktop Developers
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
    static const QString xdgDesktopName = QStringLiteral("Budgie");

    // Ensure desktop session is correct
    qputenv("DESKTOP_SESSION", xdgDesktopName.toLocal8Bit());

    // Must ensure XDG_DESKTOP_NAME is correct, display managers may end up
    // changing this which we very much do not want.
    qputenv("XDG_DESKTOP_NAME", xdgDesktopName.toLocal8Bit());

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
