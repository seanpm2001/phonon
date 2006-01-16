/*  This file is part of the KDE project
    Copyright (C) 2005 Matthias Kretz <kretz@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License version 2 as published by the Free Software Foundation.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.

*/
#include "bytestream.h"
#include "ifaces/bytestream.h"
#include "factory.h"

namespace Kdem2m
{
class ByteStream::Private
{
};

KDEM2M_HEIR_IMPL( ByteStream, AbstractMediaProducer, AbstractMediaProducer )

bool ByteStream::aboutToDeleteIface()
{
	return AbstractMediaProducer::aboutToDeleteIface();
}

void ByteStream::setupIface()
{
	AbstractMediaProducer::setupIface();

	if( !m_iface )
		return;
}

} //namespace Kdem2m

#include "bytestream.moc"

// vim: sw=4 ts=4 tw=80 noet
