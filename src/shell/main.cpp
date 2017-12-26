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

#include <QApplication>
#include <QCommandLineParser>
#include <QGuiApplication>
#include <QScopedPointer>

#include "config.h"

/**
 * Handle our basic CLI parsing with a throwaway QCoreApplication
 *
 * This ensures we don't yet use any display-context sensitive event
 * loops. Unfortunately QCommandLineParser will still try to use
 * the QCoreApplication::arguments() even if you process manually,
 * hence this entry.
 */
static void startup(int argc, char **argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("budgie-shell");
    QCoreApplication::setApplicationVersion(PACKAGE_VERSION);

    QCommandLineParser p;
    p.addHelpOption();
    p.addVersionOption();
    p.setApplicationDescription("Budgie Desktop R&D Shell");
    p.process(app);
}

/**
 * Handle the GUI specific startup routine now
 */
static QApplication *gui_main(int argc, char **argv)
{
    QGuiApplication::setFallbackSessionManagementEnabled(false);
    QApplication *ret = nullptr;

    // TODO: Maybe do something useful here
    ret = new QApplication(argc, argv);

    return ret;
}

/**
 * Main entry: Process args, begin main
 */
int main(int argc, char **argv)
{
    QScopedPointer<QApplication> gui;

    // Basic arg handling first
    startup(argc, argv);

    // Ideally we know what to do by this point, do GUI cruft.
    gui.reset(gui_main(argc, argv));
    return gui->exec();
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
