/*
 * This file is part of budgie-rd
 *
 * Copyright © 2017 Ikey Doherty <ikey@solus-project.com>
 *
 * budgie-rd is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#pragma once

#include "../panel/manager.h"
#include "../raven/raven.h"
#include "root-window.h"

#include <QObject>
#include <QScreen>

namespace Desktop
{
    class Manager : public QObject
    {
        Q_OBJECT

    public:
        explicit Manager();
        void updateGeometry();

    private:
        void updateRootWindows();

        Panel::Manager panelManager;
        Raven::Window raven;
        int numScreens;

    public slots:
        void primaryScreenChanged(QScreen *screen);
        void screenAdded(QScreen *screen);
        void screenRemoved(QScreen *screen);
    };
}
