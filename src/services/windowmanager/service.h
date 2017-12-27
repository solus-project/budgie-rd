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

#pragma once

#include <QObject>

#include "service-interface.h"

namespace Budgie
{
    /**
     * WindowManager implements basic abstraction around the window manager
     * so that it can be managed within the execution context
     */
    class Q_DECL_EXPORT WindowManagerService : public QObject, public ServiceInterface
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "org.budgie-desktop.services.WindowManager" FILE "service.json")
        Q_INTERFACES(Budgie::ServiceInterface)

    public:
        bool init(const ShellInterface *interface) override;
        bool start() override;
        bool stop() override;

    private:
        const ShellInterface *m_shell;
    };
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
