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

#include "ini-parser.h"

#include <QDebug>
#include <QFile>

namespace Desktop
{
    IniFile::IniFile() : QObject(), valid(false)
    {
    }

    IniFile::IniFile(const QString &path) : QObject(), path(path), valid(false)
    {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return;
        }

        static const auto sectionStart = QStringLiteral("[");
        static const auto sectionEnd = QStringLiteral("]");
        static const auto fieldSep = QStringLiteral("=");
        static const auto commentNorm = QStringLiteral("#");
        static const auto commentWin = QStringLiteral(";");

        QTextStream input(&file);

        QHash<QString, QString> *sectionPtr = nullptr;

        while (!input.atEnd()) {
            auto line = input.readLine().trimmed();

            if (line.isEmpty()) {
                continue;
            }

            // Starts with '#' or ';', it's a comment.
            if (line.startsWith(commentNorm) || line.startsWith(commentWin)) {
                continue;
            }

            // First up, is this a section?
            auto len = line.length();
            if (line[0] == sectionStart && line[len - 1] == sectionEnd) {
                line.remove(len - 1, 1);
                line.remove(0, 1);
                if (!mapping.contains(line)) {
                    // Shove a section in
                    mapping.insert(line,
                                   QSharedPointer<QHash<QString, QString>>(
                                       new QHash<QString, QString>()));

                    // Steal a reference to it again
                    sectionPtr = mapping[line].data();
                }
                continue;
            }

            if (!line.contains(fieldSep)) {
                continue;
            }

            if (sectionPtr == nullptr) {
                qWarning() << "Invalid INI file has no sections: " << path;
                return;
            }

            auto splits = line.split(fieldSep);
            const auto splitsLen = splits.length();
            const auto key = splits[0].trimmed();
            if (splitsLen < 2) {
                qWarning() << "INI file has missing value for key '" << key << "' @ " << path;
                continue;
            }
            // sort out the value
            splits.removeFirst();
            auto val = splits.join(fieldSep).trimmed();

            // Now stuff into the current sectionPtr
            sectionPtr->insert(key, val);
        }

        valid = true;
    }

    bool IniFile::isValid()
    {
        return this->valid;
    }

    const QString IniFile::getString(const QString &sectionID, const QString &key,
                                     const QString &fallback)
    {
        if (!mapping.contains(sectionID)) {
            return fallback;
        }
        return mapping[sectionID]->value(key, fallback);
    }

    bool IniFile::getBool(const QString &sectionID, const QString &key, bool fallback)
    {
        static const auto sTrue = QStringLiteral("true");
        static const auto sYes = QStringLiteral("yes");
        static const auto sFalse = QStringLiteral("false");

        auto ret = this->getString(sectionID, key, fallback ? sTrue : sFalse).toLower();

        if (ret.compare(sTrue, Qt::CaseInsensitive) == 0 ||
            ret.compare(sYes, Qt::CaseInsensitive) == 0) {
            return true;
        }
        return false;
    }
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
