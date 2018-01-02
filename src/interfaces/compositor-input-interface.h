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
#include "window.h"

#define BudgieCompositorInputInterfaceIID "org.budgie-desktop.CompositorInputInterface"

namespace Budgie::Compositor
{
    /**
     * The CompositorInputInterface is specific to the Compositor implementation,
     * and is used by plugins to provide specialist capabilities, such as OpenGL
     * rendering of the compositor.
     *
     * The compositor process will only have a single active renderer provider
     * at any given time, and will not provide any kind of hotswap capabilities.
     */
    class InputInterface : public BaseInterface
    {
    public:
        virtual ~InputInterface()
        {
        }

        inline const QString interfaceName() override
        {
            return QStringLiteral(BudgieCompositorInputInterfaceIID);
        }

        /* Set the current window to have mouse focus */
        virtual void setMouseFocus(Window *window) = 0;

        /* Set the current window to have key focus */
        virtual void setKeyFocus(Window *window) = 0;

        /* Send a mouse event for the given window */
        virtual void dispatchMouseEvent(QMouseEvent *e) = 0;

        /* Send a touch event for the given window */
        virtual void dispatchTouchEvent(QTouchEvent *e) = 0;

        /* Send a key event for the given window */
        virtual void dispatchKeyEvent(QKeyEvent *e) = 0;
    };
}

Q_DECLARE_INTERFACE(Budgie::Compositor::InputInterface, BudgieCompositorInputInterfaceIID)

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
