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

#include <QWaylandOutput>
#include <QWaylandOutputMode>

#include "compositor.h"

Budgie::Compositor::Compositor() : m_compositor(new QWaylandCompositor())
{
    m_wl_shell.reset(new QWaylandWlShell(m_compositor.data()));
    m_xdg_shell_v5.reset(new QWaylandXdgShellV5(m_compositor.data()));

    connect(m_compositor.data(),
            &QWaylandCompositor::createdChanged,
            this,
            &Budgie::Compositor::onCreated);
}

void Budgie::Compositor::run()
{
    auto output = new QWaylandOutput(m_compositor.data(), nullptr);
    // Add fake output, 1024x768 @ 60hz
    QWaylandOutputMode mode(QSize(1024, 768), 60000);
    output->addMode(mode, true);

    // Create our output manager
    m_window.reset(new Budgie::CompositorWindow(output));

    // Set stuff in motion now
    m_compositor->create();
}

void Budgie::Compositor::onCreated()
{
    // Again, just demo crap. Our compositor is created so set the default output
    // and display mode, and make it active.
    auto output = m_window->output();
    output->setCurrentMode(output->modes()[0]);
    m_compositor->setDefaultOutput(output);
    m_window->show();
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
