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

#include <QDebug>

#include "service.h"

bool Budgie::ShellModule::start()
{
    qDebug() << "Hello from ShellModule";

    // TODO: Pass the -s argument *somehow* ?
    m_process.reset(new QProcess());
    m_process->setProgram("budgie-rd-shell");

    connect(m_process.data(), &QProcess::errorOccurred, this, &ShellModule::processCrashed);
    connect(m_process.data(),
            QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this,
            &ShellModule::processFinished);

    // We actually want this process belonging to us, not detached.
    // Thus if someone kills the session we kill the children. Innocently, like.
    m_process->start();

    if (!m_process->waitForStarted()) {
        qWarning() << "Failed to start budgie-rd-shell";
        return false;
    }

    // At this point I guess we just assume it was ok?
    return true;
}

bool Budgie::ShellModule::stop()
{
    return true;
}

void Budgie::ShellModule::processCrashed(QProcess::ProcessError error)
{
    qDebug() << "Some kind of crash came over me: " << error;
}

void Budgie::ShellModule::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    // TODO: If exitStatus == normal exit, also close us!
    qDebug() << "exited with exitCode: " << exitCode << " and status: " << exitStatus;
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
