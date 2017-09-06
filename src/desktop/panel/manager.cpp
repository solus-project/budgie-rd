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
#include <QDesktopWidget>

namespace Panel
{
    Manager::Manager(QQmlEngine *engine) : engine(engine), demoWindow(new Window(engine))
    {
        qDebug() << "I r have a manager";
    }

    void Manager::loadPanels()
    {
        QRect r = QApplication::desktop()->screenGeometry();
        demoWindow->show();
        demoWindow->updateGeometry(r);
        qDebug() << "I haz panels nao";
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
