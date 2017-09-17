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

#include "raven-trigger.h"

#include <QHBoxLayout>

namespace Panel
{
    RavenTriggerApplet::RavenTriggerApplet(QWidget *parent) : Applet(parent)
    {
        auto layout = new QHBoxLayout();
        layout->setMargin(0);
        setLayout(layout);

        triggerButton = new QPushButton(this);
        /* TODO: Support symbolic icons .. */
        triggerButton->setIcon(QIcon::fromTheme("pane-show"));
        triggerButton->show();
        layout->addWidget(triggerButton, 0, Qt::AlignLeft | Qt::AlignVCenter);

        connect(triggerButton, &QPushButton::clicked, this, &RavenTriggerApplet::onButtonClicked);
        setObjectName("raven-trigger-applet");
    }

    void RavenTriggerApplet::onButtonClicked()
    {
        desktop()->toggleRaven();
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
