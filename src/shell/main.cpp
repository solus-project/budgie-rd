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

#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QGuiApplication>
#include <QScopedPointer>
#include <QTimer>

#include "config.h"
#include "shell.h"

/**
 * Main entry: Process args, begin main
 */
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Share refcount with timer singleShot
    QSharedPointer<Budgie::Shell::Manager> shell;

    QCoreApplication::setApplicationName("budgie-shell");
    QCoreApplication::setApplicationVersion(PACKAGE_VERSION);
    QGuiApplication::setFallbackSessionManagementEnabled(false);
    app.setQuitOnLastWindowClosed(false);

    // Set up parser
    QCommandLineParser p;
    p.addHelpOption();
    p.addVersionOption();
    p.setApplicationDescription("Budgie Desktop R&D Shell");

    // Allow setting the session type here
    QCommandLineOption optSession({ "s", "session" },
                                  QCoreApplication::translate("main", "Set the session to launch"),
                                  "session-name",
                                  "budgie-desktop");
    p.addOption(optSession);

    p.process(app);

    shell.reset(new Budgie::Shell::Manager(p.value(optSession)));

    // Sanitize our setup, ensure all services are accounted for
    if (!shell->init()) {
        qWarning() << "init(): Failed";
        return 1;
    }

    qInfo() << "Starting shell session: " << shell->sessionName();

    // Start all remaining services now on the main event loop
    QTimer::singleShot(0, [shell]() {
        if (!shell->startServices()) {
            QCoreApplication::exit(1);
            return;
        }
        if (!shell->startFace()) {
            QCoreApplication::exit(1);
            return;
        }
        qDebug() << "Budgie startup reported as nominal";
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
