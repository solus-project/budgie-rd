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

#include "face-interface.h"
#include "manager.h"
#include "raven-window.h"

namespace Budgie
{
    /**
     * DefaultFace provides the default Budgie Experience, i.e. a modern take
     * on the traditional desktop metaphor
     */
    class Q_DECL_EXPORT DefaultFace : public QObject, public FaceInterface
    {
        Q_OBJECT
        Q_PLUGIN_METADATA(IID "org.budgie-desktop.faces.Default" FILE "face.json")
        Q_INTERFACES(Budgie::FaceInterface)

    public:
        bool init(ShellInterface *interface) override;
        bool show() override;
        void shutdown() override;

    private:
        ShellInterface *m_shell;
        PanelManager *m_panelManager;
        QScopedPointer<RavenWindow> m_raven;
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
