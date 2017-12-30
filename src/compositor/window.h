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

#include <QScopedPointer>
#include <QWaylandCompositor>
#include <QWaylandOutput>
#include <QWindow>

/* OpenGL */
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLTextureBlitter>

#include "surface-item.h"

namespace Budgie
{
    /**
     * The CompositorWindow wraps a QWaylandOutput to provide actual output
     * on screen, and is responsible for rendering.
     */
    class CompositorWindow : public QWindow, protected QOpenGLFunctions
    {
        Q_OBJECT

    public:
        explicit CompositorWindow(QWaylandOutput *output);

        /**
         * Get the QWaylandOutput we're associated with
         */
        QWaylandOutput *output();

        /**
         * Get the QWaylandCompositor we're associated with
         */
        QWaylandCompositor *compositor();

    protected:
        QScopedPointer<QWaylandOutput> m_output;
        QWaylandCompositor *m_compositor;

        void scheduleDraw();

    private slots:
        void currentModeChanged();

    private:
        /* OpenGL stuff */
        QOpenGLContext *m_GLContext;
        QOpenGLTextureBlitter m_GLBlitter;

        bool event(QEvent *event) override;
        void exposeEvent(QExposeEvent *event) override;

        void ensureGL();
        void blitScreen();
        void doRender();
        void renderSurface(CompositorSurfaceItem *surface);
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
