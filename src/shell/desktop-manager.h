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

#pragma once

#include "../panel/manager.h"
#include "../raven/raven.h"
#include "root-window.h"

#include <QObject>

namespace Desktop
{
    class Manager : public QObject
    {
        Q_OBJECT

    public:
        explicit Manager(QQmlEngine *engine);
        void updateGeometry();

    private:
        QQmlEngine *engine;
        QScopedPointer<Panel::Manager> panelManager;
        Raven::Window raven;
        int numScreens;
        int primaryScreen;
        QHash<int, QSharedPointer<RootWindow>> rootWindows;

    public slots:
        void primaryScreenChanged();
        void screenCountChanged(int newCount);
        void resized(int screen);
    };
}
