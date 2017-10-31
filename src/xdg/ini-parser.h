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

#include <QHash>
#include <QObject>
#include <QSharedPointer>

namespace Desktop
{
    /**
     * IniFile allows us to safely parse unix-style INI files for use in
     * .desktop file parsing.
     * Unlike the QSettings alternative, it will actually ensure ';' is respected
     * as a separator for arrays.
     */
    class IniFile : public QObject
    {
        Q_OBJECT

    public:
        explicit IniFile();
        explicit IniFile(const QString &path);

        /**
         * Determine if this INI file is actually valid
         */
        bool isValid();

        /**
         * Grab a string from the map if it exists
         */
        const QString getString(const QString &sectionID, const QString &key,
                                const QString &fallback = QStringLiteral(""));

        /**
         * Return a QStringList for the given key
         *
         * This is typically separated by the ; character.
         */
        const QStringList getStringList(const QString &sectionID, const QString &key,
                                        const QStringList &fallback = QStringList());

        /**
         * Get a boolean value from the map. This will return false by default if the value
         * is unknown.
         */
        bool getBool(const QString &sectionID, const QString &key, bool fallback = false);

        /**
         * Simple validation - figure out if the section actually exists or not.
         */
        bool hasSection(const QString &sectionID);

    private:
        QHash<QString, QSharedPointer<QHash<QString, QString>>> mapping;
        const QString path;
        bool valid;
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
