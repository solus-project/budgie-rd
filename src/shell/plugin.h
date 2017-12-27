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
#include <QPluginLoader>

namespace Budgie
{
    /**
     * The PluginRegistry is used to locate plugins by capability and load
     * them to construct a dynamic desktop environment.
     */
    class Plugin : public QObject
    {
        Q_OBJECT

        friend class PluginRegistry;

    public:
        ~Plugin();

        /**
         * Attempt to construct a new plugin from the given filepath
         */
        static Plugin *newFromFilename(const QString &path);

        /**
         * Grab the name for this plugin
         */
        const QString &name();

        /**
         * Get the absolute filename for this plugin
         */
        const QString &fileName();

    protected:
        QScopedPointer<QPluginLoader> m_loader;

    private:
        explicit Plugin(QPluginLoader *loader);

        QString m_name;
        QString m_filename;
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
