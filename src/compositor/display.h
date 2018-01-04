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
#include "surface-item.h"
#include "windows/wayland-window.h"

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
         *
         * The index may be important to certain implementations.
         */
        explicit Display(QWaylandOutput *output, QWindow *window, uint index);

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
         * Implementations should map the surface to their output, but not
         * begin rendering it. This just ensures we connect the outputs so
         * that it is *possible* to render the surface.
         */
        virtual QWaylandView *mapSurfaceItem(SurfaceItem *item) = 0;

        /**
         * Return the view that has been allocated for the given item instance.
         * It is safe to return nullptr.
         */
        virtual QWaylandView *view(SurfaceItem *item) = 0;

        /**
         * Implementations should remove their view (if any) for the given
         * item so that it no longer renders on their display.
         */
        virtual void unmapSurfaceItem(SurfaceItem *item) = 0;

        /**
         * Implementations should override this function to return their
         * (well-ordered) list of windows that will allow input matching.
         */
        virtual QList<WaylandWindow *> inputWindows() = 0;

        /**
         * Request that the window is raised in the visual/input hierarchy. It is
         * possible we'll request raising for an unknown item. Implementations
         * should silently ignore this.
         */
        virtual void raiseWindow(WaylandWindow *window) = 0;

        /**
         * Request that the given Window is mapped and displayed on screen,
         * adding it to both the input and render lists.
         *
         * The window's root surface will already have been mapped earlier
         * through a call to mapSurfaceItem.
         *
         * The Window may be composed of child surfaces that should be painted
         * relative to the window's virtual coordinates.
         */
        virtual void mapWindow(WaylandWindow *window) = 0;

        /**
         * The unmap window routine will be called before destroying the
         * resources (via unmapSurfaceItem) so that the window can safely
         * be removed from the render and input lists.
         */
        virtual void unmapWindow(WaylandWindow *window) = 0;

        /**
         * Instruct the display to adjust their cursor surface to match the
         * given item.
         *
         * Typically cursors do not directly enter the rendering layer, and this
         * is a specialist function. Note that passing nullptr here will effectively
         * ask the implementation to unset the special cursor surface.
         */
        virtual void setCursorSurface(SurfaceItem *surface, int hotX, int hotY) = 0;

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
        uint m_index;
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
