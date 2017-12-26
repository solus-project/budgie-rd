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
    TasklistApplet::TasklistApplet() : Applet(nullptr), monitor(new Task::Monitor)
    {
        setLayout(new QBoxLayout(QBoxLayout::LeftToRight, this));
        layout()->setMargin(0);

        // Update box layout in response to panel placement
        connect(this, &Applet::orientationChanged, this, &TasklistApplet::orientationChanged);

        connect(monitor.data(), &Task::Monitor::windowOpened, this, &TasklistApplet::windowOpened);
        connect(monitor.data(), &Task::Monitor::windowClosed, this, &TasklistApplet::windowClosed);
        monitor->notifyAll();
    }

    void TasklistApplet::orientationChanged(Qt::Orientation orientation)
    {
        auto layout = qobject_cast<QBoxLayout *>(this->layout());
        if (orientation == Qt::Horizontal) {
            layout->setDirection(QBoxLayout::LeftToRight);
        } else {
            layout->setDirection(QBoxLayout::TopToBottom);
        }
    }

    void TasklistApplet::windowOpened(Task::Window *window)
    {
        if (buttons.contains(window)) {
            return;
        }

        qDebug() << "New window: " << window->title();

        static auto buttonAlign = Qt::AlignLeft | Qt::AlignTop;

        auto button = new TasklistButton(window, this);
        auto layout = qobject_cast<QBoxLayout *>(this->layout());
        layout->addWidget(button, 0, buttonAlign);
        buttons[window] = button;
        button->show();
    }

    void TasklistApplet::windowClosed(Task::Window *window)
    {
        if (!buttons.contains(window)) {
            return;
        }
        delete buttons.take(window);
        qDebug() << "Bye window: " << window->title();
    }
}
