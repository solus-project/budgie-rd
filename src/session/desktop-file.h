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

#include <QSettings>

namespace Session
{
    class DesktopFile : public QSettings
    {
        Q_OBJECT

    public:
        explicit DesktopFile();
        explicit DesktopFile(const QString &path);

        /**
         * Determine if the given .desktop file is actually valid
         */
        bool isValid();

        /**
         * Return the ID for this desktop file, i.e. "gedit.desktop"
         */
        const QString &id();

        /**
         * Determine if the item is allowed to be shown in the current desktop
         * environment.
         */
        bool canShowInDesktop(const QString &desktopName);

    private:
        bool valid;
        QString path;
        QString desktopID;
        QString desktopExec;
        QString desktopTryExec;
        QString desktopName;
        QString desktopOnlyShowIn;
        QString desktopExecutable;
        QString basename;
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
