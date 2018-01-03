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

#include <QObject>
#include <QOpenGLTextureBlitter>
#include <QOpenGLWindow>
#include <mutex>

#include "display.h"
#include "window.h"

#include "compositor-server-interface.h"
#include "renderer-view.h"

namespace Budgie::Compositor
{
    /**
     * Our OpenGLDisplay implements the basic Display type and adds specifics
     * for handling OpenGL rendering.
     */
    class OpenGLDisplay : public QOpenGLWindow, public Display
    {
        Q_OBJECT

    public:
        /**
         * Construct a new OpenGLDisplay for the given output.
         */
        OpenGLDisplay(Compositor::ServerInterface *server, QWaylandOutput *output);
        ~OpenGLDisplay();

        QWaylandView *mapWindow(Compositor::Window *window) override;
        void unmapWindow(Compositor::Window *window) override;
        QWaylandView *view(Compositor::Window *window) override;

        QList<Compositor::Window *> inputWindows() override;

        void raiseWindow(Compositor::Window *window) override;

    private:
        Compositor::ServerInterface *m_server;
        QHash<Compositor::Window *, QSharedPointer<OpenGLView>> m_views;
        QOpenGLTextureBlitter m_blitter;

        QHash<RenderLayer, QList<Compositor::Window *>> m_layers;

        QList<Compositor::Window *> m_renderables;
        QList<Compositor::Window *> m_inputWindows;

        std::mutex m_listLock;
        std::mutex m_viewLock;

        void initializeGL() override;
        void paintGL() override;
        void render();

        void moveWindowToIndex(Compositor::Window *window, int index = -1);
        void presentWindow(Compositor::Window *window);
        void unpresentWindow(Compositor::Window *window);
        void rebuildPresentables();

    protected:
        void mouseMoveEvent(QMouseEvent *e) override;
        void mousePressEvent(QMouseEvent *e) override;
        void mouseReleaseEvent(QMouseEvent *e) override;

        void keyPressEvent(QKeyEvent *e) override;
        void keyReleaseEvent(QKeyEvent *e) override;

        void touchEvent(QTouchEvent *e) override;

        void wheelEvent(QWheelEvent *e) override;

    private slots:
        void currentModeChanged();
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
