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

#include "view.h"
#include "window.h"

Budgie::CompositorView::CompositorView(Budgie::CompositorWindow *window,
                                       Budgie::CompositorSurfaceItem *surface)
    : m_window(window), m_surface(surface), m_texture(nullptr)
{
    setSurface(m_surface->surface());
    setOutput(m_window->output());
}

QOpenGLTexture *Budgie::CompositorView::texture()
{
    if (!advance()) {
        return m_texture;
    }

    auto buf = currentBuffer();
    m_texture = buf.toOpenGLTexture();
    return m_texture;
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
