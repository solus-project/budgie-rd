/*
 * This file is part of budgie-rd
 *
 * Copyright © 2017-2018 Budgie Desktop Developers
 *
 * budgie-rd is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 */

#include "taskbutton.h"

#include <QAction>
#include <QDebug>
#include <QMenu>

namespace Panel
{
    TasklistButton::TasklistButton(Task::Window *window, QWidget *parent)
        : QPushButton(parent), window(window)
    {
        connect(window, &Task::Window::iconNameChanged, this, &TasklistButton::iconNameChanged);
        connect(window, &Task::Window::titleChanged, this, &TasklistButton::titleChanged);
        connect(this, SIGNAL(released()), this, SLOT(handleRelease()));
        createActions();

        titleChanged(window->title());

        // TODO: Make sure we have fallback icons in taskmon
        iconNameChanged(window->iconName());
    }

    void TasklistButton::createActions()
    {
        minimizeAct = new QAction(tr("&Minimize"), this);
        minimizeAct->setStatusTip(tr("Minimze Window"));
        connect(minimizeAct, SIGNAL(triggered()), window, SLOT(minimize()));

        unminimizeAct = new QAction(tr("&Unminimize"), this);
        unminimizeAct->setStatusTip(tr("Unminimize Window"));
        connect(unminimizeAct, SIGNAL(triggered()), window, SLOT(activate()));
    }

    void TasklistButton::contextMenuEvent(QContextMenuEvent *event)
    {
        QMenu menu(this);
        if (window->minimized()) {
            menu.addAction(unminimizeAct);
        } else {
            menu.addAction(minimizeAct);
        }
        menu.exec(event->globalPos());
    }

    void TasklistButton::titleChanged(const QString &title)
    {
        setText(title);
    }

    void TasklistButton::iconNameChanged(const QString &iconName)
    {
        qDebug() << "Aaah an icon " << iconName;
    }

    void TasklistButton::handleRelease()
    {
        if (window->active()) {
            window->minimize();
        } else {
            window->activate();
        }
    }
}
