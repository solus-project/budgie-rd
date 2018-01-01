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

#pragma once

#include "../taskmon/task-monitor.h"

#include <QAction>
#include <QContextMenuEvent>
#include <QPushButton>
#include <QWidget>

namespace Panel
{
    class TasklistButton : public QPushButton
    {
        Q_OBJECT

    public:
        explicit TasklistButton(Task::Window *window, QWidget *parent = nullptr);

    protected:
        void contextMenuEvent(QContextMenuEvent *event) override;

    private:
        Task::Window *window;

        QAction *minimizeAct;
        QAction *unminimizeAct;

        void createActions();

    private slots:
        void iconNameChanged(const QString &iconName);
        void titleChanged(const QString &title);
        void handleRelease();
    };
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 4
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=4 tabstop=4 expandtab:
 * :indentSize=4:tabSize=4:noTabs=true:
 */
