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

#include "base-interface.h"
#include "display-interface.h"

#define BudgieWindowInterfaceIID "org.budgie-desktop.WindowInterface"

namespace Budgie
{
    /**
     * The WindowInterface provides a standard mechanism by which Budgie is
     * able to deal with top level Windows, whether they are client-side, i.e.
     * in the shell, or server-side in the compositor.
     */
    class WindowInterface : public BaseInterface
    {
    public:
        virtual ~WindowInterface()
        {
        }

        inline const QString interfaceName() override
        {
            return QStringLiteral(BudgieWindowInterfaceIID);
        }

        virtual QPoint position() = 0;
        virtual QRect geometry() = 0;
        virtual QSize size() = 0;

        /*
        virtual const QString &title() = 0;
        virtual DisplayInterface *display() = 0;


    signals:


        virtual void displayChanged() = 0;

        virtual void geometryChanged() = 0;
        */
    };
}

Q_DECLARE_INTERFACE(Budgie::WindowInterface, BudgieWindowInterfaceIID)

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
