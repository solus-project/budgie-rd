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

#include "tasklist.h"

#include <QDebug>

namespace Panel
{
    TasklistApplet::TasklistApplet() : QWidget(nullptr), monitor(new Task::Monitor)
    {
        connect(monitor.data(), &Task::Monitor::windowOpened, this, &TasklistApplet::windowOpened);
        connect(monitor.data(), &Task::Monitor::windowClosed, this, &TasklistApplet::windowClosed);
        monitor->notifyAll();
    }

    void TasklistApplet::windowOpened(Task::Window *window)
    {
        qDebug() << "New window: " << window->title();
    }

    void TasklistApplet::windowClosed(Task::Window *window)
    {
        qDebug() << "Bye window: " << window->title();
    }
}
