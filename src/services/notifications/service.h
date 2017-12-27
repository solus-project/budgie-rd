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
     * NotificationService provides the XDG notifications service for
     * Budgie, and will in future provide the D-BUS service, plus an
     * easily accessible data model for the desktop to access.
     *
     * The NotificationService is loaded prior to any available graphical
     * context and may cache unseen notifications from early services, such
     * as printing and power alerts, so that they can safely be displayed
     * once our main plugin is up and running.
     */
    class Q_DECL_EXPORT NotificationService : public QObject, public ServiceInterface
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "org.budgie-desktop.services.Notifications" FILE "service.json")
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
