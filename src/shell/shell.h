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
#include <QSharedPointer>

#include "registry.h"
#include "shell-interface.h"

namespace Budgie
{
    /**
     * The Budgie::Shell is the basic execution environment for Budgie
     * and uses the PluginRegistry to create and maintain a desktop environment.
     */
    class Shell : public QObject, public ShellInterface
    {
        Q_OBJECT

    public:
        explicit Shell(const QString &name);

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
         * Start absolutely essential services, usually this is just the
         * window manager itself, just to ensure we have a valid graphical
         * context before constructing an application.
         */
        bool startEssential();

        /**
         * Now continue with executing the rest of the services and begin
         * a full shell startup
         */
        bool startRemaining();

        /**
         * Now we have the service lifecycle started, launch the face
         */
        bool startFace();

        /* ShellInterface methods */
        bool registerInterface(const QString &id, QObject *interface) override;
        const QObject *getInterface(const QString &id) override;
        bool hasInterface(const QString &id) override;

    private:
        QSharedPointer<PluginRegistry> m_registry;
        QString m_sessionName;

        QString m_faceName;

        QStringList m_essentialServices;
        QStringList m_standardServices;

        QHash<QString, QObject *> m_interfaces;

        bool startServiceSet(const QStringList &serviceIDs, bool fatal);
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
