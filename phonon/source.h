/*  This file is part of the KDE project
    Copyright (C) 2007 Matthias Kretz <kretz@kde.org>

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

#ifndef PHONON_SOURCE_H
#define PHONON_SOURCE_H

#include "phononglobal.h"

#include <QtCore/QSharedData>

class QUrl;
class QIODevice;

namespace Phonon
{

class SourcePrivate;
class AbstractMediaStream;

class PHONON_EXPORT Source
{
public:
    enum DeviceType {
        NoDevice = -1,
        AudioCd,
        VideoCd,
        Dvd,
        BluRay,
        AudioCapture,
        VideoCapture
    };
public:
    Source();
    Source(const Source &other);
    Source(const QUrl &url);
    Source(DeviceType deviceType, const QByteArray &deviceName = QByteArray());
    Source(AbstractMediaStream *stream);
    Source(QIODevice *ioDevice);

    // FIXME: why is the dtor virtual?
    virtual ~Source();

    Source &operator=(const Source &other);
    bool operator==(const Source &other) const;

    QUrl url() const;
    DeviceType deviceType() const;
    QByteArray deviceName() const;
    AbstractMediaStream *stream() const;

protected:
    QExplicitlySharedDataPointer<SourcePrivate> d;
    Source(SourcePrivate &);
};

} // namespace Phonon

#endif // PHONON_SOURCE_H
