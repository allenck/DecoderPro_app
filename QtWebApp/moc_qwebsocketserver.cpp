/****************************************************************************
** Meta object code from reading C++ file 'qwebsocketserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtwebsockets/src/websockets/qwebsocketserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwebsocketserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QWebSocketServer_t {
    QByteArrayData data[25];
    char stringdata0[396];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QWebSocketServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QWebSocketServer_t qt_meta_stringdata_QWebSocketServer = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QWebSocketServer"
QT_MOC_LITERAL(1, 17, 11), // "acceptError"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(4, 59, 11), // "socketError"
QT_MOC_LITERAL(5, 71, 11), // "serverError"
QT_MOC_LITERAL(6, 83, 29), // "QWebSocketProtocol::CloseCode"
QT_MOC_LITERAL(7, 113, 9), // "closeCode"
QT_MOC_LITERAL(8, 123, 28), // "originAuthenticationRequired"
QT_MOC_LITERAL(9, 152, 28), // "QWebSocketCorsAuthenticator*"
QT_MOC_LITERAL(10, 181, 14), // "pAuthenticator"
QT_MOC_LITERAL(11, 196, 13), // "newConnection"
QT_MOC_LITERAL(12, 210, 15), // "peerVerifyError"
QT_MOC_LITERAL(13, 226, 9), // "QSslError"
QT_MOC_LITERAL(14, 236, 5), // "error"
QT_MOC_LITERAL(15, 242, 9), // "sslErrors"
QT_MOC_LITERAL(16, 252, 16), // "QList<QSslError>"
QT_MOC_LITERAL(17, 269, 6), // "errors"
QT_MOC_LITERAL(18, 276, 34), // "preSharedKeyAuthenticationReq..."
QT_MOC_LITERAL(19, 311, 30), // "QSslPreSharedKeyAuthenticator*"
QT_MOC_LITERAL(20, 342, 13), // "authenticator"
QT_MOC_LITERAL(21, 356, 6), // "closed"
QT_MOC_LITERAL(22, 363, 7), // "SslMode"
QT_MOC_LITERAL(23, 371, 10), // "SecureMode"
QT_MOC_LITERAL(24, 382, 13) // "NonSecureMode"

    },
    "QWebSocketServer\0acceptError\0\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "serverError\0QWebSocketProtocol::CloseCode\0"
    "closeCode\0originAuthenticationRequired\0"
    "QWebSocketCorsAuthenticator*\0"
    "pAuthenticator\0newConnection\0"
    "peerVerifyError\0QSslError\0error\0"
    "sslErrors\0QList<QSslError>\0errors\0"
    "preSharedKeyAuthenticationRequired\0"
    "QSslPreSharedKeyAuthenticator*\0"
    "authenticator\0closed\0SslMode\0SecureMode\0"
    "NonSecureMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QWebSocketServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       1,   74, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       5,    1,   57,    2, 0x06 /* Public */,
       8,    1,   60,    2, 0x06 /* Public */,
      11,    0,   63,    2, 0x06 /* Public */,
      12,    1,   64,    2, 0x06 /* Public */,
      15,    1,   67,    2, 0x06 /* Public */,
      18,    1,   70,    2, 0x06 /* Public */,
      21,    0,   73,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void,

 // enums: name, flags, count, data
      22, 0x0,    2,   78,

 // enum data: key, value
      23, uint(QWebSocketServer::SecureMode),
      24, uint(QWebSocketServer::NonSecureMode),

       0        // eod
};

void QWebSocketServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QWebSocketServer *_t = static_cast<QWebSocketServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->acceptError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 1: _t->serverError((*reinterpret_cast< QWebSocketProtocol::CloseCode(*)>(_a[1]))); break;
        case 2: _t->originAuthenticationRequired((*reinterpret_cast< QWebSocketCorsAuthenticator*(*)>(_a[1]))); break;
        case 3: _t->newConnection(); break;
        case 4: _t->peerVerifyError((*reinterpret_cast< const QSslError(*)>(_a[1]))); break;
        case 5: _t->sslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        case 6: _t->preSharedKeyAuthenticationRequired((*reinterpret_cast< QSslPreSharedKeyAuthenticator*(*)>(_a[1]))); break;
        case 7: _t->closed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QWebSocketServer::*)(QAbstractSocket::SocketError );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketServer::acceptError)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QWebSocketServer::*)(QWebSocketProtocol::CloseCode );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketServer::serverError)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QWebSocketServer::*)(QWebSocketCorsAuthenticator * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketServer::originAuthenticationRequired)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QWebSocketServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketServer::newConnection)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QWebSocketServer::*)(const QSslError & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketServer::peerVerifyError)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QWebSocketServer::*)(const QList<QSslError> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketServer::sslErrors)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QWebSocketServer::*)(QSslPreSharedKeyAuthenticator * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketServer::preSharedKeyAuthenticationRequired)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (QWebSocketServer::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketServer::closed)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QWebSocketServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QWebSocketServer.data,
      qt_meta_data_QWebSocketServer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QWebSocketServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QWebSocketServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QWebSocketServer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QWebSocketServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void QWebSocketServer::acceptError(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QWebSocketServer::serverError(QWebSocketProtocol::CloseCode _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QWebSocketServer::originAuthenticationRequired(QWebSocketCorsAuthenticator * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QWebSocketServer::newConnection()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void QWebSocketServer::peerVerifyError(const QSslError & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QWebSocketServer::sslErrors(const QList<QSslError> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QWebSocketServer::preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QWebSocketServer::closed()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
