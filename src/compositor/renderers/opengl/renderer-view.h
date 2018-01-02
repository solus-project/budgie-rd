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
#include <QWaylandView>

#include "window.h"

namespace Budgie::Compositor
{
    /**
     * Our OpenGLView implements a basic View for OpenGL rendering of a
     * given surface.
     */
    class OpenGLView : public QWaylandView
    {
        Q_OBJECT

    public:
        /**
         * Construct a new OpenGLView for the given output.
         */
        OpenGLView(Window *window);

    private:
        Window *m_window;
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
