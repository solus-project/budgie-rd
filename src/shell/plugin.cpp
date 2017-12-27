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

#include <QDebug>
#include <QLibrary>
#include <QScopedPointer>

#include "plugin.h"

Budgie::Plugin *Budgie::Plugin::newFromFilename(const QString &filename)
{
    QScopedPointer<QPluginLoader> loader(new QPluginLoader(filename));
    loader->setLoadHints(QLibrary::ResolveAllSymbolsHint);
    if (!loader->load()) {
        qDebug() << "Failed to load plugin \"" << filename << "\": " << loader->errorString();
        return nullptr;
    }
    return new Budgie::Plugin(loader.take());
}

Budgie::Plugin::Plugin(QPluginLoader *loader) : m_loader(loader)
{
    m_filename = m_loader->fileName();
    auto json = m_loader->metaData().toVariantMap();
    m_name = m_loader->metaData().value("IID").toString();
    qDebug() << "New plugin loaded: " << m_name;
}

Budgie::Plugin::~Plugin()
{
    // Always attempt to unload the library when we're being destroyed
    m_loader->unload();
}

const QString &Budgie::Plugin::name()
{
    return m_name;
}

const QString &Budgie::Plugin::fileName()
{
    return m_filename;
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
