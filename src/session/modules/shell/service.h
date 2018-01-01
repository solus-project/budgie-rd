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
#include <QProcess>
#include <QScopedPointer>

#include "session-module-interface.h"

namespace Budgie
{
    /**
     * Shell is launched after WindowManagerModule achieves a successful start
     * and will attempt to launch the main shell process.
     */
    class Q_DECL_EXPORT ShellModule : public QObject, public SessionModuleInterface
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "org.budgie-desktop.session.Shell" FILE "service.json")
        Q_INTERFACES(Budgie::SessionModuleInterface)

    public:
        bool start() override;
        bool stop() override;

    private slots:
        void processCrashed(QProcess::ProcessError e);
        void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

    private:
        QScopedPointer<QProcess> m_process;
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
