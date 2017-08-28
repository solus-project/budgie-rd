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

#include <QScreen>
#include <QWidget>

namespace Desktop
{
    class RootWindow : public QWidget
    {
        Q_OBJECT

    public:
        explicit RootWindow(int screenNumber);
        void updateGeometry();

    private:
        int screenNumber;
        QRect visibleArea;
    };
}
