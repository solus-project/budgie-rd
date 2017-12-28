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

#include <KWindowEffects>
#include <QBoxLayout>
#include <QEvent>

#include "window.h"

Budgie::PanelWindow::PanelWindow(ShellInterface *interface) : m_shell(interface)
{
    move(0, 1080 - 30);
    setFixedSize(1920, 30);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_X11NetWmWindowTypeDock);
    setAttribute(Qt::WA_X11DoNotAcceptFocus);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setFocusPolicy(Qt::NoFocus);

    auto rootWidget = new QWidget(this);
    auto layout = new QHBoxLayout;
    this->setLayout(layout);
    layout->addWidget(rootWidget);
    layout->setMargin(0);

    // Clear any existing styles.
    setStyleSheet("background-color: rgba(0, 0, 0, 0);");

    // Colour picking
    rootWidget->setObjectName("budgie-panel");
    rootWidget->setStyleSheet("#budgie-panel { background-color: rgba(34, 49, 63, 0.89); }");
    rootWidget->setLayout(new QBoxLayout(QBoxLayout::LeftToRight));
    rootWidget->layout()->setMargin(0);

    ensurePolished();
}

Budgie::PanelWindow::~PanelWindow()
{
}

bool Budgie::PanelWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::WinIdChange:
        m_winID = effectiveWinId();
        updateWindow();
        return true;
    default:
        return QWidget::event(event);
    }
}

void Budgie::PanelWindow::updateWindow()
{
    // TODO: Abstract this through a well known interface!
    // For now just set blur/etc, which will later be dock-specific controls..
    KWindowEffects::enableBlurBehind(m_winID);
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
