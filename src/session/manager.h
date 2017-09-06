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

#include <QCoreApplication>
#include <QHash>

namespace Session
{
    class Manager : public QCoreApplication
    {
        Q_OBJECT

    public:
        explicit Manager(int &argc, char **argv);

    private:
        QList<QString> appDirs;
        QString homeDir;
        QHash<QString, QString> appIds;

        /**
         * Quick helper to determine if a given autostart directory actually
         * does exist or not.
         */
        void appendAutostartDirectory(const QString &directory);

        /**
         * Scan the startup directories to find required components and to
         * build a proper mapping
         */
        void scanApps();

        /**
         * Push an application to the autostart monitor based on its ID.
         * It is then up to the core handler to determine what to do with
         * it after.
         */
        void pushAutostartAppID(const QString &id);
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
