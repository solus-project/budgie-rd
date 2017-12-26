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

#include "applet.h"

namespace Panel
{
    Applet::Applet(QWidget *parent) : QWidget(parent), appletOrientation(Qt::Horizontal)
    {
    }

    Qt::Orientation Applet::orientation()
    {
        return this->appletOrientation;
    }

    void Applet::setOrientation(Qt::Orientation orient)
    {
        if (orient == this->appletOrientation) {
            return;
        }
        this->appletOrientation = orient;
        emit orientationChanged(this->appletOrientation);
    }

    void Applet::setDesktopInterface(Desktop::ManagerInterface *iface)
    {
        this->desktopIface = iface;
    }

    Desktop::ManagerInterface *Applet::desktop()
    {
        return this->desktopIface;
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
