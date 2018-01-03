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
#include "compositor-server-interface.h"
#include "display.h"

#define BudgieCompositorRendererInterfaceIID "org.budgie-desktop.CompositorRendererInterface"

namespace Budgie::Compositor
{
    /**
     * The CompositorRendererInterface is specific to the Compositor implementation,
     * and is used by plugins to provide specialist capabilities, such as OpenGL
     * rendering of the compositor.
     *
     * The compositor process will only have a single active renderer provider
     * at any given time, and will not provide any kind of hotswap capabilities.
     */
    class RendererInterface : public BaseInterface
    {
    public:
        virtual ~RendererInterface()
        {
        }

        inline const QString interfaceName() override
        {
            return QStringLiteral(BudgieCompositorRendererInterfaceIID);
        }

        /**
         * Construct a new DisplayInterface for the given Wayland output.
         * The process will terminate if it is not possible to construct
         * a display here.
         *
         * Note this API is specialist to the Compositor and requires end
         * users to link against libbudgie-compositor-shared.
         */
        virtual Display *createDisplay(Compositor::ServerInterface *server,
                                       QWaylandOutput *output) = 0;
    };
}

Q_DECLARE_INTERFACE(Budgie::Compositor::RendererInterface, BudgieCompositorRendererInterfaceIID)

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
