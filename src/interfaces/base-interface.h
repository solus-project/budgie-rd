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

#define BudgieBaseInterfaceIID "org.budgie-desktop.BaseInterface"

namespace Budgie
{
    /* Forward declare all classes */
    class BaseInterface;
    class FaceInterface;
    class PanelInterface;
    class PanelManagerInterface;
    class RavenInterface;
    class ServiceInterface;
    class ShellInterface;

    /* WM interfaces */
    class DisplayInterface;
    class WindowInterface;
    class WindowManagerInterface;

    /* Compositor interfaces */
    namespace Compositor
    {
        class Display;
        class InputInterface;
        class RendererInterface;
    }

    /**
     * All interfaces within Budgie derive from the BaseInterface.
     */
    class BaseInterface
    {
    public:
        virtual ~BaseInterface()
        {
        }

        virtual const QString interfaceName() = 0;
    };
}

Q_DECLARE_INTERFACE(Budgie::BaseInterface, BudgieBaseInterfaceIID)

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
