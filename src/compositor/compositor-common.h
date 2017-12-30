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

#include <QObject>

namespace Budgie
{
    Q_NAMESPACE

    /* Helps us to control which "layer" something will be rendered on
     * as we'll render back-to-front
     *
     * Each chain is also back-to-front for rendering order to permit z-stacking
     * within each layer.
     */
    enum RenderLayer {
        BACKGROUND = 0, /* Wallpaper */
        DESKTOP,        /* Desktop icons */
        APPLICATION,    /* Ordinary applications */
        PANEL,          /* Budgie Panel/docks */
        SIDEBAR,        /* Raven */
        FULLSCREEN,     /* Exclusive fullscreen */
        NOTIFICATION,   /* OSD, etc */
        DND,            /* Show DND icons always, but below cursor */
        CURSOR,         /* Cursor is rendered above everything else */
    };

    Q_ENUM_NS(RenderLayer)

    /* Forward declare all our classes */
    class Compositor;
    class CompositorSurfaceItem;
    class CompositorWindow;
    class CompositorView;
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
