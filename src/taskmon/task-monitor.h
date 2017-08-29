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

#include <KWindowSystem>
#include <QObject>

namespace Task
{
    class Monitor : public QObject
    {
        Q_OBJECT

    public:
        explicit Monitor();

    private slots:
        void windowAdded(WId id);
        void windowChanged(WId id, NET::Properties props, NET::Properties2 props2);
        void windowRemoved(WId id);
    };
}
