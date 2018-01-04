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

#include <QAbstractAnimation>
#include <QCoreApplication>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

#include "compositor-renderer-interface.h"
#include "display.h"
#include "server.h"

using namespace Budgie::Compositor;

Server::Server(RendererInterface *renderer)
    : m_renderer(renderer), m_wl_shell(new QWaylandWlShell(this)),
      m_xdg_shell_v5(new QWaylandXdgShellV5(this)), m_seat(nullptr)
{
    // Start with zero focus
    m_keyFocus = nullptr;
    m_mouseFocus = nullptr;
    m_mouseLast = QPoint(0, 0);

    // Hook up basic compositor signals so we know whats going on when we ::create()
    connect(this, &QWaylandCompositor::surfaceCreated, this, &Server::surfaceCreated);
    connect(this, &QWaylandCompositor::surfaceAboutToBeDestroyed, this, &Server::surfaceDestroying);

    // Now hook up each protocol
    connect(m_wl_shell, &QWaylandWlShell::wlShellSurfaceCreated, this, &Server::wlShellCreated);
    connect(m_xdg_shell_v5,
            &QWaylandXdgShellV5::xdgSurfaceCreated,
            this,
            &Server::xdgShellv5Created);

    connect(this, &QWaylandCompositor::defaultSeatChanged, this, &Server::wlSeatChanged);
    connect(this, &QWaylandCompositor::createdChanged, this, &Server::wlCreated);
}

bool Server::start()
{
    // Ask that we get created.
    create();

    // This is where we just fake the hell out of it for now.
    auto output = new QWaylandOutput(this, nullptr);
    QWaylandOutputMode mode(QSize(1024, 768), 60000);
    output->setPosition(QPoint(0, 0));
    output->addMode(mode, true);

    // This is code we WOULD use, i.e. construct a display and store it.
    // We'll actually need to add sorting based on the index but in theory
    // we could swap to a map of index->display
    auto display = m_renderer->createDisplay(this, output, 0);
    if (!display) {
        qWarning() << "Failed to construct a valid display for: " << output;
        return false;
    }

    auto window = display->window();
    if (window == nullptr) {
        qWarning() << "Broken Renderer is not returning the SurfaceItem";
        return false;
    }

    // Force connection and mode change now
    output->setWindow(window);
    output->setCurrentMode(mode);

    // Store the display now
    m_displays << QSharedPointer<Display>(display);

    // Get it on screen
    window->show();
    return true;
}

/**
 * Return the initial display to map the new SurfaceItem to.
 *
 * For now we're just going to return our primary display but in future this
 * will be the one with the current mouse focus.
 */
Display *Server::initialDisplay(SurfaceItem *item)
{
    Q_UNUSED(item);
    // TODO: Something not sucky :')
    return m_displays[0].data();
}

/**
 * The interfaces have encountered a case where a window is now required,
 * so stash the window.
 */
void Server::promoteWindow(WaylandWindow *window)
{
    qDebug() << "Found Window: " << window;

    // Store this guy so its deleted later.
    m_windows.insert(window->rootSurface(), QSharedPointer<WaylandWindow>(window));

    // Preset some properties for the animation before the first frame is drawn
    // otherwise it'll jank.
    window->setOpacity(0.0);
    window->setScale(QVector2D(0.3, 0.3));

    // TODO: Find out where the feck this thing is meant to be showing.
    // We'll need to store each Display in the window structure..
    initialDisplay(window->rootSurface())->mapWindow(window);

    auto group = new QParallelAnimationGroup();
    // This is just a super basic example to show we can do animations too.
    // The rendering is done with the shader
    auto animation = new QPropertyAnimation(window, "opacity");
    animation->setDuration(250);
    animation->setStartValue(0.0);
    animation->setEndValue(1.0);
    group->addAnimation(animation);

    // Incredibly childish animation, couldn't help it
    animation = new QPropertyAnimation(window, "scale");
    animation->setEasingCurve(QEasingCurve::OutElastic);
    animation->setDuration(900);
    animation->setStartValue(QVector2D(0.3, 0.3));
    animation->setEndValue(QVector2D(1.0, 1.0));
    group->addAnimation(animation);

    group->start(QAbstractAnimation::DeleteWhenStopped);
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
