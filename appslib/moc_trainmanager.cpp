/****************************************************************************
** Meta object code from reading C++ file 'trainmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/trainmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trainmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__TrainManager_t {
    QByteArrayData data[8];
    char stringdata[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__TrainManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__TrainManager_t qt_meta_stringdata_Operations__TrainManager = {
    {
QT_MOC_LITERAL(0, 0, 24), // "Operations::TrainManager"
QT_MOC_LITERAL(1, 25, 14), // "propertyChange"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(4, 62, 1), // "e"
QT_MOC_LITERAL(5, 64, 7), // "onError"
QT_MOC_LITERAL(6, 72, 5), // "title"
QT_MOC_LITERAL(7, 78, 3) // "msg"

    },
    "Operations::TrainManager\0propertyChange\0"
    "\0PropertyChangeEvent*\0e\0onError\0title\0"
    "msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__TrainManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       5,    2,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,    7,

       0        // eod
};

void Operations::TrainManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrainManager *_t = static_cast<TrainManager *>(_o);
        switch (_id) {
        case 0: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 1: _t->onError((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< PropertyChangeEvent* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Operations::TrainManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Operations__TrainManager.data,
      qt_meta_data_Operations__TrainManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::TrainManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::TrainManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__TrainManager.stringdata))
        return static_cast<void*>(const_cast< TrainManager*>(this));
    return QObject::qt_metacast(_clname);
}

int Operations::TrainManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_Operations__MyBuild_t {
    QByteArrayData data[7];
    char stringdata[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__MyBuild_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__MyBuild_t qt_meta_stringdata_Operations__MyBuild = {
    {
QT_MOC_LITERAL(0, 0, 19), // "Operations::MyBuild"
QT_MOC_LITERAL(1, 20, 8), // "finished"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "error"
QT_MOC_LITERAL(4, 36, 5), // "title"
QT_MOC_LITERAL(5, 42, 3), // "msg"
QT_MOC_LITERAL(6, 46, 7) // "process"

    },
    "Operations::MyBuild\0finished\0\0error\0"
    "title\0msg\0process"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__MyBuild[] = {

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
       3,    2,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Operations::MyBuild::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyBuild *_t = static_cast<MyBuild *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->error((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->process(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MyBuild::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyBuild::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (MyBuild::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MyBuild::error)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Operations::MyBuild::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Operations__MyBuild.data,
      qt_meta_data_Operations__MyBuild,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::MyBuild::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::MyBuild::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__MyBuild.stringdata))
        return static_cast<void*>(const_cast< MyBuild*>(this));
    return QObject::qt_metacast(_clname);
}

int Operations::MyBuild::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Operations::MyBuild::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Operations::MyBuild::error(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
