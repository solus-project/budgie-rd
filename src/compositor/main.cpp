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
#include <QGuiApplication>
#include <QTimer>

#include "config.h"
#include "manager.h"

/**
 * Main Compositor entry
 *
 * Bootstrap the budgie-rd-compositor and show pretty pictures on screen.
 */
int main(int argc, char **argv)
{
    // Causes massive leaks
    qputenv("QT_NO_GLIB", "1");

    // Support NVIDIA.
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts, true);
    QGuiApplication app(argc, argv);
    QSharedPointer<Budgie::Compositor::Manager> comp;

    QCoreApplication::setApplicationName("budgie-compositor");
    QCoreApplication::setApplicationVersion(PACKAGE_VERSION);
    QGuiApplication::setFallbackSessionManagementEnabled(false);
    // app.setQuitOnLastWindowClosed(false);

    // Set up parser
    QCommandLineParser p;
    p.addHelpOption();
    p.addVersionOption();
    p.setApplicationDescription("Budgie Desktop R&D Compositor");
    p.process(app);

    comp.reset(new Budgie::Compositor::Manager());

    if (!comp->init()) {
        qWarning() << "init(): Failed";
        return 1;
    }

    // Run once idle loop is active
    QTimer::singleShot(0, [comp] {
        if (!comp->start()) {
            QCoreApplication::exit(1);
            return;
        }
        qDebug() << "Compositor startup reported as nominal";
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
