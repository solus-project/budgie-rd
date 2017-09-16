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

#include "taskbutton.h"

#include <QDebug>

namespace Panel
{
    TasklistButton::TasklistButton(Task::Window *window, QWidget *parent)
        : QPushButton(parent), window(window)
    {
        connect(window, &Task::Window::iconNameChanged, this, &TasklistButton::iconNameChanged);
        connect(window, &Task::Window::titleChanged, this, &TasklistButton::titleChanged);

        titleChanged(window->title());

        // TODO: Make sure we have fallback icons in taskmon
        iconNameChanged(window->iconName());
    }

    void TasklistButton::titleChanged(const QString &title)
    {
        setText(title);
    }

    void TasklistButton::iconNameChanged(const QString &iconName)
    {
        qDebug() << "Aaah an icon " << iconName;
    }
}
