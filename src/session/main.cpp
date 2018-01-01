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

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

#include "config.h"
#include "session.h"

/**
 * Handle any session-specific desktop overrides we need to put in place.
 * Currently this is setting the xdg desktop name/session name for this
 * process and all descendants.
 */
static void initEnvironment()
{
    QString xdgDesktopName = "Budgie";
    auto xdgLocal = xdgDesktopName.toLocal8Bit();

    // Ensure desktop session is correct
    qputenv("DESKTOP_SESSION", xdgLocal);

    // Must ensure XDG_DESKTOP_NAME is correct, display managers may end up
    // changing this which we very much do not want.
    qputenv("XDG_DESKTOP_NAME", xdgLocal);
}

/**
 * Main Budgie entry.
 *
 * The session is responsible for bootstrapping the initial environment and
 * then launching critical desktop services, including the window manager,
 * shell, and finally any XDG autostart applications.
 *
 * This can be extended through the PluginRegistry to provide additional
 * core services to the Session.
 */
int main(int argc, char **argv)
{
    // Before any real Qt usage
    initEnvironment();

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("budgie-session");
    QCoreApplication::setApplicationVersion(PACKAGE_VERSION);

    // Set up parser
    QCommandLineParser p;
    p.addHelpOption();
    p.addVersionOption();
    p.setApplicationDescription("Budgie Desktop R&D Session");

    // Allow setting the session type here
    QCommandLineOption optSession({ "s", "session" },
                                  QCoreApplication::translate("main", "Set the session to launch"),
                                  "session-name",
                                  "budgie-desktop");
    p.addOption(optSession);
    p.process(app);

    // Sanitize our setup, ensure all services are accounted for
    QSharedPointer<Budgie::Session::Manager> session(
        new Budgie::Session::Manager(p.value(optSession)));

    if (!session->init()) {
        qWarning() << "init(): Failed";
        return 1;
    }

    qInfo() << "Starting session session: " << session->sessionName();

    // Start all services now on the main event loop
    QTimer::singleShot(0, [session]() {
        if (!session->start()) {
            QCoreApplication::exit(1);
            return;
        }
        qDebug() << "Budgie session startup reported as nominal";
    });

    return app.exec();
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
