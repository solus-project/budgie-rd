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

#include "task-monitor.h"

#include <KWindowSystem>
#include <QDebug>

namespace Task
{
    Monitor::Monitor()
    {
        auto instance = KWindowSystem::self();
        connect(instance, &KWindowSystem::windowAdded, this, &Monitor::kwinWindowAdded);
        // Could C++ be any more messed up...
        connect(instance,
                static_cast<void (KWindowSystem::*)(WId, NET::Properties, NET::Properties2)>(
                    &KWindowSystem::windowChanged),
                this,
                &Monitor::kwinWindowChanged);
        connect(instance, &KWindowSystem::windowRemoved, this, &Monitor::kwinWindowRemoved);
    }

    /**
     * New window added, hook it up to the monitor
     */
    void Monitor::kwinWindowAdded(WId id)
    {
        if (windows.contains(id)) {
            return;
        }
        windows.insert(id, QSharedPointer<Window>(new Window(id)));
        emit windowOpened(windows[id].data());
    }

    /**
     * A window has changed, update the state
     */
    void Monitor::kwinWindowChanged(WId id, NET::Properties props, NET::Properties2 props2)
    {
        Q_UNUSED(props2);

        if (!windows.contains(id)) {
            qDebug() << "KWindowSystem reports change for invalid window..";
            return;
        }

        Window *window = windows[id].data();
        KWindowInfo info(id, props, props2);

        if (!info.valid()) {
            return;
        }

        /* icon name change */
        if (props & NET::WMIconName) {
            window->setIconName(info.iconName());
        }

        /* title change */
        if (props & NET::WMName) {
            window->setTitle(info.name());
        }
    }

    /**
     * A window was removed, nuke it from the monitor
     */
    void Monitor::kwinWindowRemoved(WId id)
    {
        if (!windows.contains(id)) {
            qDebug() << "KWindowSystem reported invalid window close...";
            return;
        }
        emit windowClosed(windows[id].data());
        windows.remove(id);
    }
}
