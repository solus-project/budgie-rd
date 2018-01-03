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

#include <QList>
#include <QScopedPointer>
#include <QWaylandOutput>
#include <QWaylandView>
#include <QWindow>

#include "display-interface.h"
#include "window.h"

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
         * Implementations should construct a view for the given window
         * and begin rendering it within their display.
         *
         * The View should be returned so that the window manager is free
         * to set the primary view if necessary.
         */
        virtual QWaylandView *mapWindow(Window *window) = 0;

        /**
         * Return the view that has been allocated for the given window instance.
         * It is safe to return nullptr.
         */
        virtual QWaylandView *view(Window *window) = 0;

        /**
         * Implementations should remove their view (if any) for the given
         * window so that it no longer renders on their display.
         */
        virtual void unmapWindow(Window *window) = 0;

        /**
         * Implementations should override this to return their list of
         * candidate windows which are eligible for input region matching.
         */
        virtual QList<Window *> inputWindows() = 0;

        /**
         * Request that the window is raised in the visual/input hierarchy. It is
         * possible we'll request raising for an unknown window. Implementations
         * should silently ignore this.
         */
        virtual void raiseWindow(Window *window) = 0;

        /**
         * A Wayland display knows its index in Budgie
         */
        uint index() override;

        /**
         * Return the geometry of the Wayland display
         */
        QRect geometry() override;

    protected:
        QScopedPointer<QWaylandOutput> m_output;
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
