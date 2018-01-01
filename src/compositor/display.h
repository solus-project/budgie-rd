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

#include <QWaylandOutput>
#include <QWindow>

#include "display-interface.h"

namespace Budgie::Compositor
{
    /**
     * Each display is a Wayland specific display implementation of the
     * DisplayInterface, and needs further extending by the primary
     * Renderer.
     */
    class Display : public DisplayInterface
    {
    public:
        virtual ~Display()
        {
        }

        /**
         * Subclasses should chain the constructor appropriately.
         */
        explicit Display(QWaylandOutput *output, QWindow *window);

        /**
         * Return the QWindow for this Display so that the output can be
         * correctly connected.
         */
        virtual QWindow *window();

        /**
         * Return the Display that was used to initialise this display
         */
        QWaylandOutput *output();

        /**
         * A Wayland display knows its index in Budgie
         */
        uint index() override;

        /**
         * Return the geometry of the Wayland display
         */
        QRect geometry() override;

    protected:
        QWaylandOutput *m_output;
        QWindow *m_window;
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
