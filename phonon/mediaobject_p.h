/*  This file is part of the KDE project
    Copyright (C) 2006-2007 Matthias Kretz <kretz@kde.org>

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

#ifndef MEDIAOBJECT_P_H
#define MEDIAOBJECT_P_H

#include "mediaobject.h"
#include "medianode_p.h"
#include <QtCore/QString>
#include "medianodedestructionhandler_p.h"
#include "mediasource.h"
#include <QtCore/QQueue>
#ifdef HAVE_QZEITGEIST
#include <QtZeitgeist/Log>
#include <QtZeitgeist/QtZeitgeist>
#endif

QT_BEGIN_NAMESPACE

namespace Phonon
{
class KioFallback;
class KioFallbackImpl;
class FrontendInterfacePrivate;

class MediaObjectPrivate : public MediaNodePrivate, private MediaNodeDestructionHandler
{
    friend class KioFallbackImpl;
    friend class AbstractMediaStream;
    friend class AbstractMediaStreamPrivate;
    Q_DECLARE_PUBLIC(MediaObject)
    public:
        virtual QObject *qObject() { return q_func(); }

        /**
         * Sends the metadata for this media file to the Zeitgeist tracker
         *
         * \param eventInterpretation The interpretation of the event
         * \param eventManifestation The manifestation type of the event
         * \param eventActor The application or entity responsible for emitting the zeitgeist event
         * \param eventTimestamp The time
         * \param subjectURI The file's URI
         * \param subjectText A free-form annotation
         * \param subjectInterpretation The interpretation type
         * \param subjectManifestation The manifestation type
         * \param subjectMimetype The file's mimetype
         */
        void sendToZeitgeist(const QString &event_interpretation,
                             const QString &event_manifestation,
                             const QString &event_actor,
                             const QDateTime &subject_timestamp,
                             const QUrl &subject_uri,
                             const QString &subject_text,
                             const QString &subject_interpretation,
                             const QString &subject_manifestation,
                             const QString &subject_mimetype);

        void sendToZeitgeist(State);
        void sendToZeitgeist();

    QList<FrontendInterfacePrivate *> interfaceList;
    protected:
        virtual bool aboutToDeleteBackendObject();
        virtual void createBackendObject();
        virtual void phononObjectDestroyed(MediaNodePrivate *);
        PHONON_EXPORT void setupBackendObject();

        void _k_resumePlay();
        void _k_resumePause();
        void _k_metaDataChanged(const QMultiMap<QString, QString> &);
        void _k_aboutToFinish();
        void _k_currentSourceChanged(const MediaSource &);
        PHONON_EXPORT void _k_stateChanged(Phonon::State, Phonon::State);
        void streamError(Phonon::ErrorType, const QString &);

        MediaObjectPrivate()
            : currentTime(0),
            tickInterval(0),
            metaData(),
            errorString(),
            prefinishMark(0),
            transitionTime(0), // gapless playback
            abstractStream(0),
            state(Phonon::LoadingState),
            readyForZeitgeist(false)
            , errorType(Phonon::NormalError),
            errorOverride(false),
            ignoreLoadingToBufferingStateChange(false),
            ignoreErrorToLoadingStateChange(false)
        {
#ifdef HAVE_QZEITGEIST
            QtZeitgeist::init();
            log = new QtZeitgeist::Log(qObject());
#endif
        }

        qint64 currentTime;
        qint32 tickInterval;
        QMultiMap<QString, QString> metaData;
        QString errorString;
        qint32 prefinishMark;
        qint32 transitionTime;
        AbstractMediaStream *abstractStream;
        State state : 8;
        bool readyForZeitgeist;
        ErrorType errorType : 4;
        bool errorOverride : 1;
        bool ignoreLoadingToBufferingStateChange : 1;
        bool ignoreErrorToLoadingStateChange : 1;
        MediaSource mediaSource;
        QQueue<MediaSource> sourceQueue;
#ifdef HAVE_QZEITGEIST
        QtZeitgeist::Log *log;
#endif
};
}

QT_END_NAMESPACE

#endif // MEDIAOBJECT_P_H
// vim: sw=4 ts=4 tw=80
