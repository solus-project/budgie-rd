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

#include "shell-registry.h"

using namespace Budgie::Shell;

Registry::Registry()
{
    // We only care about services/faces
    appendSearchPath(systemDirectory().filePath("services"));
    appendSearchPath(systemDirectory().filePath("faces"));
}

QSharedPointer<Budgie::ServiceInterface> Registry::getService(const QString &name)
{
    return getPlugin<Budgie::ServiceInterface>(QStringLiteral("services/") + name);
}

QSharedPointer<Budgie::FaceInterface> Registry::getFace(const QString &name)
{
    return getPlugin<Budgie::FaceInterface>(QStringLiteral("faces/") + name);
}

bool Registry::hasServicePlugin(const QString &name)
{
    return hasPlugin(QStringLiteral("services/") + name);
}

bool Registry::hasFacePlugin(const QString &name)
{
    return hasPlugin(QStringLiteral("faces/") + name);
}

void Registry::unloadFace(const QString &face)
{
    unload("faces/" + face);
}

void Registry::unloadService(const QString &service)
{
    unload("services/" + service);
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
