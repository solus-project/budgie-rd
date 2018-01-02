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

#include "renderer-view.h"

using namespace Budgie::Compositor;

OpenGLView::OpenGLView(Compositor::Window *window)
    : m_window(window), m_texture(nullptr), m_textureOrigin(QOpenGLTextureBlitter::OriginBottomLeft)
{
    auto surface = m_window->surface();
    setSurface(surface);
}

/**
 * Lightly influenced by the QWayland demo + QOpenGLTextureBlitter docs.
 */
QOpenGLTexture *OpenGLView::texture()
{
    if (!advance()) {
        return m_texture;
    }

    // Cache our texture reference + origin
    auto buffer = currentBuffer();
    m_texture = buffer.toOpenGLTexture();
    auto origin = buffer.origin();
    if (origin == QWaylandSurface::OriginTopLeft) {
        m_textureOrigin = QOpenGLTextureBlitter::OriginTopLeft;
    } else {
        m_textureOrigin = QOpenGLTextureBlitter::OriginBottomLeft;
    }

    return m_texture;
}

QOpenGLTextureBlitter::Origin OpenGLView::textureOrigin()
{
    return m_textureOrigin;
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
