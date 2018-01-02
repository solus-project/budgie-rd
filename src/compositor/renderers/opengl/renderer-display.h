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
#include <QOpenGLWindow>

#include "display.h"
#include "window.h"

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
        OpenGLDisplay(QWaylandOutput *output);

        void mapWindow(Compositor::Window *window) override;
        void unmapWindow(Compositor::Window *window) override;

    private:
        void initializeGL() override;
        void paintGL() override;

        void render();

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
