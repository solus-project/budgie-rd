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
#include "icon-provider.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QQuickStyle>
#include <QQuickWindow>

int main(int argc, char *argv[])
{
    QGuiApplication::setFallbackSessionManagementEnabled(false);

    // RGBA windows pls
    QQuickWindow::setDefaultAlphaBuffer(true);
    QQuickStyle::setStyle("Material");

    QApplication app(argc, argv);

    // TODO: Take from a config.h
    QCoreApplication::setApplicationName("budgie-shell");
    QCoreApplication::setApplicationVersion("0.0.0");

    QCommandLineParser p;
    p.addHelpOption();
    p.addVersionOption();
    p.setApplicationDescription("Budgie Desktop R&D Shell");
    p.process(app);

    QQmlEngine engine;
    engine.addImageProvider(QLatin1String("icon-theme"), new Desktop::IconThemeProvider());

    Desktop::Manager manager(&engine);
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
