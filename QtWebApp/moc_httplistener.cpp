/****************************************************************************
** Meta object code from reading C++ file 'httplistener.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "httpserver/httplistener.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httplistener.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_stefanfrings__HttpListener_t {
    QByteArrayData data[5];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_stefanfrings__HttpListener_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_stefanfrings__HttpListener_t qt_meta_stringdata_stefanfrings__HttpListener = {
    {
QT_MOC_LITERAL(0, 0, 26), // "stefanfrings::HttpListener"
QT_MOC_LITERAL(1, 27, 16), // "handleConnection"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 17), // "tSocketDescriptor"
QT_MOC_LITERAL(4, 63, 16) // "socketDescriptor"

    },
    "stefanfrings::HttpListener\0handleConnection\0"
    "\0tSocketDescriptor\0socketDescriptor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_stefanfrings__HttpListener[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void stefanfrings::HttpListener::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HttpListener *_t = static_cast<HttpListener *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->handleConnection((*reinterpret_cast< tSocketDescriptor(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HttpListener::*)(tSocketDescriptor );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpListener::handleConnection)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject stefanfrings::HttpListener::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_stefanfrings__HttpListener.data,
      qt_meta_data_stefanfrings__HttpListener,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *stefanfrings::HttpListener::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *stefanfrings::HttpListener::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_stefanfrings__HttpListener.stringdata0))
        return static_cast<void*>(this);
    return QTcpServer::qt_metacast(_clname);
}

int stefanfrings::HttpListener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void stefanfrings::HttpListener::handleConnection(tSocketDescriptor _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
