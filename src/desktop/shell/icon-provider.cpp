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

#include "icon-provider.h"

#include <QIcon>

namespace Desktop
{
    IconThemeProvider::IconThemeProvider() : QQuickImageProvider(QQuickImageProvider::Pixmap)
    {
        // TODO: Track/control icon theme property for the process..?
    }

    QPixmap IconThemeProvider::requestPixmap(const QString &id, QSize *size,
                                             const QSize &requestedSize)
    {
        static const int fallbackSize = 32;

        // TODO: check -symbolic suffix
        QIcon ico = QIcon::fromTheme(id);
        QPixmap pix;

        if (requestedSize.isValid()) {
            pix = ico.pixmap(requestedSize);
        } else {
            pix = ico.pixmap(fallbackSize, fallbackSize);
        }
        if (size != nullptr) {
            *size = pix.size();
        }
        return pix;
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
