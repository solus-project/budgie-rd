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

#include "desktop-manager.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QQuickWindow>

int main(int argc, char *argv[])
{
    // RGBA windows pls
    QQuickWindow::setDefaultAlphaBuffer(true);

    QApplication app(argc, argv);

    // TODO: Take from a config.h
    QCoreApplication::setApplicationName("budgie-shell");
    QCoreApplication::setApplicationVersion("0.0.0");

    QCommandLineParser p;
    p.addHelpOption();
    p.addVersionOption();
    p.setApplicationDescription("Budgie Desktop R&D Shell");
    p.process(app);

    Desktop::Manager manager;
    return app.exec();
}
