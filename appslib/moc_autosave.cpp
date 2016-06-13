/****************************************************************************
** Meta object code from reading C++ file 'autosave.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/autosave.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'autosave.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__AutoSave_t {
    QByteArrayData data[1];
    char stringdata[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__AutoSave_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__AutoSave_t qt_meta_stringdata_Operations__AutoSave = {
    {
QT_MOC_LITERAL(0, 0, 20) // "Operations::AutoSave"

    },
    "Operations::AutoSave"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__AutoSave[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Operations::AutoSave::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Operations::AutoSave::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Operations__AutoSave.data,
      qt_meta_data_Operations__AutoSave,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::AutoSave::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::AutoSave::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__AutoSave.stringdata))
        return static_cast<void*>(const_cast< AutoSave*>(this));
    return QObject::qt_metacast(_clname);
}

int Operations::AutoSave::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_Operations__Worker_t {
    QByteArrayData data[6];
    char stringdata[47];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__Worker_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__Worker_t qt_meta_stringdata_Operations__Worker = {
    {
QT_MOC_LITERAL(0, 0, 18), // "Operations::Worker"
QT_MOC_LITERAL(1, 19, 8), // "finished"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "error"
QT_MOC_LITERAL(4, 35, 3), // "err"
QT_MOC_LITERAL(5, 39, 7) // "process"

    },
    "Operations::Worker\0finished\0\0error\0"
    "err\0process"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__Worker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Operations::Worker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Worker *_t = static_cast<Worker *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->process(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Worker::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Worker::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (Worker::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Worker::error)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Operations::Worker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Operations__Worker.data,
      qt_meta_data_Operations__Worker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::Worker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::Worker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__Worker.stringdata))
        return static_cast<void*>(const_cast< Worker*>(this));
    return QObject::qt_metacast(_clname);
}

int Operations::Worker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Operations::Worker::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Operations::Worker::error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
