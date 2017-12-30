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
#include <QWaylandCompositor>

namespace Budgie
{
    /**
     * The Budgie::Compositor handles the lifecycle for the main compositor
     * process, and will load the relevant implementation to handle actually
     * rendering.
     */
    class Compositor : public QObject
    {
        Q_OBJECT

    public:
        explicit Compositor();

        /**
         * Request that the compositor now run, i.e. create the server.
         */
        void run();

    private:
        QSharedPointer<QWaylandCompositor> m_compositor;
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
