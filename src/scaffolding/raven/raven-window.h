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

#include <QWidget>

#include "raven-interface.h"

namespace Budgie::Raven
{
    /**
     * The main window implements the RavenInterface and provides the
     * user with a sidebar style control that allows access to various
     * extensions, notifications, etc.
     */
    class Window : public QWidget, public RavenInterface
    {
        Q_OBJECT

    public:
        explicit Window(ShellInterface *interface);
        ~Window();

        /* Overrides */
        void show() override;
        void hide() override;
        void toggle() override;

    private:
        ShellInterface *m_shell;
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
