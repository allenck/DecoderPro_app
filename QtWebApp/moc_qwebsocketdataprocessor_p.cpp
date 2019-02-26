/****************************************************************************
** Meta object code from reading C++ file 'qwebsocketdataprocessor_p.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qtwebsockets/src/websockets/qwebsocketdataprocessor_p.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwebsocketdataprocessor_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QWebSocketDataProcessor_t {
    QByteArrayData data[23];
    char stringdata0[295];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QWebSocketDataProcessor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QWebSocketDataProcessor_t qt_meta_stringdata_QWebSocketDataProcessor = {
    {
QT_MOC_LITERAL(0, 0, 23), // "QWebSocketDataProcessor"
QT_MOC_LITERAL(1, 24, 12), // "pingReceived"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "data"
QT_MOC_LITERAL(4, 43, 12), // "pongReceived"
QT_MOC_LITERAL(5, 56, 13), // "closeReceived"
QT_MOC_LITERAL(6, 70, 29), // "QWebSocketProtocol::CloseCode"
QT_MOC_LITERAL(7, 100, 9), // "closeCode"
QT_MOC_LITERAL(8, 110, 11), // "closeReason"
QT_MOC_LITERAL(9, 122, 17), // "textFrameReceived"
QT_MOC_LITERAL(10, 140, 5), // "frame"
QT_MOC_LITERAL(11, 146, 9), // "lastFrame"
QT_MOC_LITERAL(12, 156, 19), // "binaryFrameReceived"
QT_MOC_LITERAL(13, 176, 19), // "textMessageReceived"
QT_MOC_LITERAL(14, 196, 7), // "message"
QT_MOC_LITERAL(15, 204, 21), // "binaryMessageReceived"
QT_MOC_LITERAL(16, 226, 16), // "errorEncountered"
QT_MOC_LITERAL(17, 243, 4), // "code"
QT_MOC_LITERAL(18, 248, 11), // "description"
QT_MOC_LITERAL(19, 260, 7), // "process"
QT_MOC_LITERAL(20, 268, 10), // "QIODevice*"
QT_MOC_LITERAL(21, 279, 9), // "pIoDevice"
QT_MOC_LITERAL(22, 289, 5) // "clear"

    },
    "QWebSocketDataProcessor\0pingReceived\0"
    "\0data\0pongReceived\0closeReceived\0"
    "QWebSocketProtocol::CloseCode\0closeCode\0"
    "closeReason\0textFrameReceived\0frame\0"
    "lastFrame\0binaryFrameReceived\0"
    "textMessageReceived\0message\0"
    "binaryMessageReceived\0errorEncountered\0"
    "code\0description\0process\0QIODevice*\0"
    "pIoDevice\0clear"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QWebSocketDataProcessor[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       5,    2,   70,    2, 0x06 /* Public */,
       9,    2,   75,    2, 0x06 /* Public */,
      12,    2,   80,    2, 0x06 /* Public */,
      13,    1,   85,    2, 0x06 /* Public */,
      15,    1,   88,    2, 0x06 /* Public */,
      16,    2,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      19,    1,   96,    2, 0x0a /* Public */,
      22,    0,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QString,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   10,   11,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::Bool,   10,   11,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QByteArray,   14,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QString,   17,   18,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,

       0        // eod
};

void QWebSocketDataProcessor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QWebSocketDataProcessor *_t = static_cast<QWebSocketDataProcessor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pingReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->pongReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->closeReceived((*reinterpret_cast< QWebSocketProtocol::CloseCode(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->textFrameReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->binaryFrameReceived((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->textMessageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->binaryMessageReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 7: _t->errorEncountered((*reinterpret_cast< QWebSocketProtocol::CloseCode(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->process((*reinterpret_cast< QIODevice*(*)>(_a[1]))); break;
        case 9: _t->clear(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QWebSocketDataProcessor::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketDataProcessor::pingReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QWebSocketDataProcessor::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketDataProcessor::pongReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (QWebSocketDataProcessor::*)(QWebSocketProtocol::CloseCode , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketDataProcessor::closeReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (QWebSocketDataProcessor::*)(const QString & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketDataProcessor::textFrameReceived)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (QWebSocketDataProcessor::*)(const QByteArray & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketDataProcessor::binaryFrameReceived)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (QWebSocketDataProcessor::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketDataProcessor::textMessageReceived)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (QWebSocketDataProcessor::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketDataProcessor::binaryMessageReceived)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (QWebSocketDataProcessor::*)(QWebSocketProtocol::CloseCode , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QWebSocketDataProcessor::errorEncountered)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QWebSocketDataProcessor::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QWebSocketDataProcessor.data,
      qt_meta_data_QWebSocketDataProcessor,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QWebSocketDataProcessor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QWebSocketDataProcessor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QWebSocketDataProcessor.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int QWebSocketDataProcessor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void QWebSocketDataProcessor::pingReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QWebSocketDataProcessor::pongReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QWebSocketDataProcessor::closeReceived(QWebSocketProtocol::CloseCode _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QWebSocketDataProcessor::textFrameReceived(const QString & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QWebSocketDataProcessor::binaryFrameReceived(const QByteArray & _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QWebSocketDataProcessor::textMessageReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void QWebSocketDataProcessor::binaryMessageReceived(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void QWebSocketDataProcessor::errorEncountered(QWebSocketProtocol::CloseCode _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
