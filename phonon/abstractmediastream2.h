/*
    Copyright (C) 2011 Harald Sitter <sitter@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) version 3, or any
    later version accepted by the membership of KDE e.V. (or its
    successor approved by the membership of KDE e.V.), Nokia Corporation
    (or its successors, if any) and the KDE Free Qt Foundation, which shall
    act as a proxy defined in Section 6 of version 3 of the license.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PHONON_ABSTRACTMEDIASTREAM2_H
#define PHONON_ABSTRACTMEDIASTREAM2_H

#include "abstractmediastream.h"

namespace Phonon {

class AbstractMediaStream2 : public AbstractMediaStream
{
    Q_OBJECT
public:
    virtual ~AbstractMediaStream2();

protected:
    explicit AbstractMediaStream2(QObject *parent = 0);

    Q_INVOKABLE virtual void needData(qint64 size) = 0;

    void resetDone();

#warning todo: add start/stop explicitly

private:
    void needData() {};
};

} // namespace Phonon

#endif // PHONON_ABSTRACTMEDIASTREAM2_H