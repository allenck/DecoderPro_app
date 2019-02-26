/****************************************************************************
** Meta object code from reading C++ file 'httpconnectionhandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "httpserver/httpconnectionhandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpconnectionhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_stefanfrings__HttpConnectionHandler_t {
    QByteArrayData data[20];
    char stringdata0[313];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_stefanfrings__HttpConnectionHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_stefanfrings__HttpConnectionHandler_t qt_meta_stringdata_stefanfrings__HttpConnectionHandler = {
    {
QT_MOC_LITERAL(0, 0, 35), // "stefanfrings::HttpConnectionH..."
QT_MOC_LITERAL(1, 36, 16), // "handleConnection"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 17), // "tSocketDescriptor"
QT_MOC_LITERAL(4, 72, 16), // "socketDescriptor"
QT_MOC_LITERAL(5, 89, 11), // "readTimeout"
QT_MOC_LITERAL(6, 101, 4), // "read"
QT_MOC_LITERAL(7, 106, 20), // "websocketTextMessage"
QT_MOC_LITERAL(8, 127, 4), // "data"
QT_MOC_LITERAL(9, 132, 28), // "websocketbinaryFrameReceived"
QT_MOC_LITERAL(10, 161, 5), // "final"
QT_MOC_LITERAL(11, 167, 12), // "disconnected"
QT_MOC_LITERAL(12, 180, 8), // "readHttp"
QT_MOC_LITERAL(13, 189, 34), // "preSharedKeyAuthenticationReq..."
QT_MOC_LITERAL(14, 224, 30), // "QSslPreSharedKeyAuthenticator*"
QT_MOC_LITERAL(15, 255, 13), // "authenticator"
QT_MOC_LITERAL(16, 269, 9), // "encrypted"
QT_MOC_LITERAL(17, 279, 9), // "sslErrors"
QT_MOC_LITERAL(18, 289, 16), // "QList<QSslError>"
QT_MOC_LITERAL(19, 306, 6) // "errors"

    },
    "stefanfrings::HttpConnectionHandler\0"
    "handleConnection\0\0tSocketDescriptor\0"
    "socketDescriptor\0readTimeout\0read\0"
    "websocketTextMessage\0data\0"
    "websocketbinaryFrameReceived\0final\0"
    "disconnected\0readHttp\0"
    "preSharedKeyAuthenticationRequired\0"
    "QSslPreSharedKeyAuthenticator*\0"
    "authenticator\0encrypted\0sslErrors\0"
    "QList<QSslError>\0errors"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_stefanfrings__HttpConnectionHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    1,   69,    2, 0x08 /* Private */,
       9,    2,   72,    2, 0x08 /* Private */,
      11,    0,   77,    2, 0x08 /* Private */,
      12,    0,   78,    2, 0x08 /* Private */,
      13,    1,   79,    2, 0x08 /* Private */,
      16,    0,   82,    2, 0x08 /* Private */,
      17,    1,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Bool,    8,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void stefanfrings::HttpConnectionHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HttpConnectionHandler *_t = static_cast<HttpConnectionHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleConnection((*reinterpret_cast< tSocketDescriptor(*)>(_a[1]))); break;
        case 1: _t->readTimeout(); break;
        case 2: _t->read(); break;
        case 3: _t->websocketTextMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->websocketbinaryFrameReceived((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->disconnected(); break;
        case 6: _t->readHttp(); break;
        case 7: _t->preSharedKeyAuthenticationRequired((*reinterpret_cast< QSslPreSharedKeyAuthenticator*(*)>(_a[1]))); break;
        case 8: _t->encrypted(); break;
        case 9: _t->sslErrors((*reinterpret_cast< const QList<QSslError>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject stefanfrings::HttpConnectionHandler::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_stefanfrings__HttpConnectionHandler.data,
      qt_meta_data_stefanfrings__HttpConnectionHandler,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *stefanfrings::HttpConnectionHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stefanfrings::HttpConnectionHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_stefanfrings__HttpConnectionHandler.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int stefanfrings::HttpConnectionHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
