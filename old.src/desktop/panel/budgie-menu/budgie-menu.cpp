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

#include "budgie-menu.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QObject>

namespace Panel
{
    MenuApplet::MenuApplet(QWidget *parent) : Applet(parent)
    {
        auto layout = new QHBoxLayout();
        layout->setMargin(0);
        setLayout(layout);

        menuWindow.reset(new MenuWindow());

        auto icon = QIcon::fromTheme("start-here");

        mainButton = new QPushButton(QStringLiteral("Menu"), this);
        mainButton->setFlat(true);
        mainButton->setIcon(icon);
        mainButton->setObjectName("budgie-menu-button");
        mainButton->show();
        layout->addWidget(mainButton, 1);

        // Hook up for clicks
        connect(mainButton, &QPushButton::clicked, this, &MenuApplet::buttonClicked);

        setObjectName("budgie-menu-applet");
    }

    void MenuApplet::buttonClicked()
    {
        menuWindow->toggleVisibility(this->mainButton);
    }
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
