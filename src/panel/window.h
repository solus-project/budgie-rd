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

#include <QWidget>

namespace Budgie::Panel
{
    class Window : public QWidget
    {
        Q_OBJECT
        Q_ENUMS(Position)

    public:
        enum Position {
            Undetermined,
            Top,
            Left,
            Right,
            Bottom,
        };

        explicit Window();
        void updateGeometry(QRect &rect, Position p = Position::Top);

    private:
        int intendedSize;
    };
}
