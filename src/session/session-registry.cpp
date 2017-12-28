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

#include "session-registry.h"

Budgie::SessionRegistry::SessionRegistry()
{
    // We only care about session
    appendSearchPath(systemDirectory().filePath("session"));
}

QSharedPointer<Budgie::SessionModuleInterface> Budgie::SessionRegistry::getSessionModule(
    const QString &name)
{
    return getPlugin<Budgie::SessionModuleInterface>(QStringLiteral("session/") + name);
}

bool Budgie::SessionRegistry::hasSessionModule(const QString &name)
{
    return hasPlugin(QStringLiteral("session/") + name);
}

void Budgie::SessionRegistry::unloadSessionModule(const QString &name)
{
    unload("session/" + name);
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
