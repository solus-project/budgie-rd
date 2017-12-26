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

#include "config.h"

/**
 * Main entry into Budgie.
 * Effectively start the application lifecycle, and then load all the relevant
 * services/providers to build a desktop environment for the user.
 */
int main(int argc, char **argv)
{
    QGuiApplication::setFallbackSessionManagementEnabled(false);

    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("budgie-shell");
    QCoreApplication::setApplicationVersion(PACKAGE_VERSION);

    QCommandLineParser p;
    p.addHelpOption();
    p.addVersionOption();
    p.setApplicationDescription("Budgie Desktop R&D Shell");
    p.process(app);

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
