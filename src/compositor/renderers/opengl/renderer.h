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
#include <QWaylandOutput>

#include "compositor-input-interface.h"
#include "compositor-renderer-interface.h"
#include "display.h"

namespace Budgie::Compositor
{
    /**
     * OpenGLRenderer provides an OpenGL based renderering plugin for the
     * Budgie Compositor.
     */
    class Q_DECL_EXPORT OpenGLRenderer : public QObject, public RendererInterface
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "org.budgie-desktop.compositor.OpenGLRenderer" FILE "renderer.json")
        Q_INTERFACES(Budgie::Compositor::RendererInterface)

    public:
        void init(Compositor::InputInterface *input) override;
        Display *createDisplay(QWaylandOutput *output) override;

    private:
        Compositor::InputInterface *m_input;
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
