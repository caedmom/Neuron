/**************************************************************************
**
** This file is part of Noron.
** https://github.com/HamedMasafi/Noron
**
** Noron is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Noron is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with Noron.  If not, see <http://www.gnu.org/licenses/>.
**
**************************************************************************/

#ifndef NORONABSTRACTHUB_P_H
#define NORONABSTRACTHUB_P_H

#include <QtCore/QSet>

#include <QMutex>

#include "noronabstracthub.h"

#define ID                  "_id"
#define CLASS_NAME          "_c"
#define METHOD_NAME         "_m"
#define MAP_TYPE            "_t"
#define MAP_RETURN_VALUE    "_return_value"
#define MAP_TYPE_REQUEST    "request"
#define MAP_TYPE_RESPONSE   "response"
#define MAP_TOKEN_ITEM      "_token"

class QTcpSocket;
class QJSEngine;
class QQmlEngine;

NORON_BEGIN_NAMESPACE

class NoronAbstractHubPrivate{
    NoronAbstractHub *q_ptr;
    Q_DECLARE_PUBLIC(NoronAbstractHub)

public:
    NoronAbstractHubPrivate(NoronAbstractHub *parent);

    QSet<QString> locks;
    QVariantList buffer;
    QByteArray readBuffer;
    QHash<const QString, NoronSharedObject*> sharedObjects;
    QMutex socketReadMutes;

    NoronPeer* peer;
    QString validateToken;
    NoronAbstractSerializer* serializer;
    qlonglong requestId;
    bool isTransaction;
    bool isMultiThread;
    qlonglong hubId;
    NoronAbstractHub::Status status;

#ifdef QT_QML_LIB
    QJSEngine *jsEngine;
    QQmlEngine *qmlEngine;
#endif

    void addToMap(QVariantMap *map, QVariant var, int index);
    void procMap(QVariantList list);
    void procMap(QVariantMap map);
    bool response(const qlonglong &id, const QString &senderName, const QVariant &returnValue);
    QString createValidateToken(QVariantMap &map);
    void addValidateToken(QVariantMap &map);
    bool checkValidateToken(QVariantMap &map);
    QString MD5(const QString &text);
    QString MD5(QByteArray text);
    void sync();
};

NORON_END_NAMESPACE

#endif // NORONABSTRACTHUB_P_H
