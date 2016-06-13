/****************************************************************************
** Meta object code from reading C++ file 'train.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/train.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'train.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__Train_t {
    QByteArrayData data[14];
    char stringdata[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__Train_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__Train_t qt_meta_stringdata_Operations__Train = {
    {
QT_MOC_LITERAL(0, 0, 17), // "Operations::Train"
QT_MOC_LITERAL(1, 18, 5), // "error"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 14), // "propertyChange"
QT_MOC_LITERAL(4, 40, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(5, 61, 1), // "e"
QT_MOC_LITERAL(6, 63, 8), // "on_error"
QT_MOC_LITERAL(7, 72, 5), // "title"
QT_MOC_LITERAL(8, 78, 3), // "msg"
QT_MOC_LITERAL(9, 82, 7), // "OPTIONS"
QT_MOC_LITERAL(10, 90, 14), // "CHANGE_ENGINES"
QT_MOC_LITERAL(11, 105, 14), // "HELPER_ENGINES"
QT_MOC_LITERAL(12, 120, 11), // "ADD_CABOOSE"
QT_MOC_LITERAL(13, 132, 14) // "REMOVE_CABOOSE"

    },
    "Operations::Train\0error\0\0propertyChange\0"
    "PropertyChangeEvent*\0e\0on_error\0title\0"
    "msg\0OPTIONS\0CHANGE_ENGINES\0HELPER_ENGINES\0"
    "ADD_CABOOSE\0REMOVE_CABOOSE"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__Train[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       1,   42, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   34,    2, 0x0a /* Public */,
       6,    2,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    8,

 // enums: name, flags, count, data
       9, 0x0,    4,   46,

 // enum data: key, value
      10, uint(Operations::Train::CHANGE_ENGINES),
      11, uint(Operations::Train::HELPER_ENGINES),
      12, uint(Operations::Train::ADD_CABOOSE),
      13, uint(Operations::Train::REMOVE_CABOOSE),

       0        // eod
};

void Operations::Train::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Train *_t = static_cast<Train *>(_o);
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 2: _t->on_error((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PropertyChangeEvent* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Train::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Train::error)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Operations::Train::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Operations__Train.data,
      qt_meta_data_Operations__Train,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::Train::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::Train::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__Train.stringdata))
        return static_cast<void*>(const_cast< Train*>(this));
    return QObject::qt_metacast(_clname);
}

int Operations::Train::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Operations::Train::error(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
