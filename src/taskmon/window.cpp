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

#include "window.h"

#include <KWindowSystem>
#include <QString>

namespace Task
{
    Window::Window(WId id) : id(id)
    {
        // Only query 1 props, not 2props
        // static unsigned int initialQuery = NET::WMName | NET::WMWindowType | NET::WMIcon |
        // NET::WMIconName
        static auto initialQuery = NET::WMName | NET::WMIconName;
        KWindowInfo info(id, initialQuery, static_cast<NET::Property2>(0));

        // Consider support for visibleName() the KWin <2> suffix style
        winTitle = info.name();
        winIcon = info.iconName();
    }

    const QString Window::title()
    {
        return this->winTitle;
    }

    const QString Window::iconName()
    {
        return this->winIcon;
    }
}
