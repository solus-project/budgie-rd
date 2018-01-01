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
#include <QSharedPointer>

#include "shell-interface.h"
#include "shell-registry.h"

namespace Budgie::Shell
{
    /**
     * The Shell::Manager is the basic execution environment for Budgie
     * and uses the PluginRegistry to create and maintain a desktop environment.
     */
    class Manager : public QObject, public ShellInterface
    {
        Q_OBJECT

    public:
        explicit Manager(const QString &name);

        /**
         * Get the name for this Shell environment
         */
        const QString &sessionName() override;

        /**
         * Attempt early initialisation of Shell, i.e. begin
         * search for our plugins.
         */
        bool init();

        /**
         * Start the services we require to support the rest of the shell,
         * such as the notifications service. This is all performed via
         * plugin loads before we ever show the UI.
         */
        bool startServices();

        /**
         * Now we have the service lifecycle started, launch the face
         */
        bool startFace();

        /* ShellInterface methods */
        void shutdown() override;
        bool registerInterface(BaseInterface *interface, const QString &id = nullptr) override;
        BaseInterface *getInterface(const QString &id) override;
        bool hasInterface(const QString &id) override;
        PanelManagerInterface *getPanelManager() override;
        RavenInterface *getRaven() override;

    private slots:
        void shutdownShell();

    private:
        QSharedPointer<Registry> m_registry;
        QString m_sessionName;

        QString m_faceName;

        QStringList m_requiredServices;
        QStringList m_activeServices;

        QHash<QString, BaseInterface *> m_interfaces;

        bool m_shutdownRequested;
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
