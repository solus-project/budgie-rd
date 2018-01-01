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

#include "clock.h"

#include <QDateTime>
#include <QDebug>
#include <QHBoxLayout>
#include <QObject>

namespace Panel
{
    ClockApplet::ClockApplet(QWidget *parent) : Applet(parent)
    {
        auto layout = new QHBoxLayout();
        layout->setMargin(0);
        setLayout(layout);
        lab = new QLabel(this);
        lab->show();
        layout->addWidget(lab, 0, Qt::AlignLeft | Qt::AlignVCenter);

        timer.reset(new QTimer());

        connect(timer.data(), &QTimer::timeout, this, &ClockApplet::onTimer);

        // Prediction of the first time where the time changed
        // 59 - QDateTime::currentDateTime().time().second() + 2
        timer->setInterval((61 - QDateTime::currentDateTime().time().second()) * 1000);
        timer->start();

        setObjectName("budgie-clock-applet");
        // TODO: Not be a jackass.
        setStyleSheet("#budgie-clock-applet QLabel { color: white; }");

        lab->setText(QDateTime::currentDateTime().toString(QStringLiteral("hh:mm")));
    }

    void ClockApplet::onTimer()
    {
        // Set to 60s instead of the first Interval
        timer.setInterval(60000);
        QString now = QDateTime::currentDateTime().toString(QStringLiteral("hh:mm"));

        // Nonly update the label if it actually changes ..
        if (now != lab->text()) {
            lab->setText(now);
        }
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
