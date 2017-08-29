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

namespace Task
{
    Monitor::Monitor()
    {
        auto instance = KWindowSystem::self();
        connect(instance, &KWindowSystem::windowAdded, this, &Monitor::windowAdded);
        // Could C++ be any more messed up...
        connect(instance,
                static_cast<void (KWindowSystem::*)(WId, NET::Properties, NET::Properties2)>(
                    &KWindowSystem::windowChanged),
                this,
                &Monitor::windowChanged);
        connect(instance, &KWindowSystem::windowRemoved, this, &Monitor::windowRemoved);
    }

    /**
     * New window added, hook it up to the monitor
     */
    void Monitor::windowAdded(WId id)
    {
        Q_UNUSED(id);
    }

    /**
     * A window has changed, update the state
     */
    void Monitor::windowChanged(WId id, NET::Properties props, NET::Properties2 props2)
    {
        Q_UNUSED(id);
        Q_UNUSED(props);
        Q_UNUSED(props2);
    }

    /**
     * A window was removed, nuke it from the monitor
     */
    void Monitor::windowRemoved(WId id)
    {
        Q_UNUSED(id);
    }
}
