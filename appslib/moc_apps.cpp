/****************************************************************************
** Meta object code from reading C++ file 'apps.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "apps.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apps.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Apps_t {
    QByteArrayData data[6];
    char stringdata[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Apps_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Apps_t qt_meta_stringdata_Apps = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Apps"
QT_MOC_LITERAL(1, 5, 14), // "propertyChange"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(4, 42, 2), // "ev"
QT_MOC_LITERAL(5, 45, 13) // "On_handleQuit"

    },
    "Apps\0propertyChange\0\0PropertyChangeEvent*\0"
    "ev\0On_handleQuit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Apps[] = {

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
       5,    0,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void Apps::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Apps *_t = static_cast<Apps *>(_o);
        switch (_id) {
        case 0: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 1: _t->On_handleQuit(); break;
        default: ;
        }
    }
}

const QMetaObject Apps::staticMetaObject = {
    { &JmriJFrame::staticMetaObject, qt_meta_stringdata_Apps.data,
      qt_meta_data_Apps,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Apps::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Apps::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Apps.stringdata))
        return static_cast<void*>(const_cast< Apps*>(this));
    return JmriJFrame::qt_metacast(_clname);
}

int Apps::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = JmriJFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_WriteBlocksShutdownTask_t {
    QByteArrayData data[3];
    char stringdata[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WriteBlocksShutdownTask_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WriteBlocksShutdownTask_t qt_meta_stringdata_WriteBlocksShutdownTask = {
    {
QT_MOC_LITERAL(0, 0, 23), // "WriteBlocksShutdownTask"
QT_MOC_LITERAL(1, 24, 7), // "execute"
QT_MOC_LITERAL(2, 32, 0) // ""

    },
    "WriteBlocksShutdownTask\0execute\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WriteBlocksShutdownTask[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Bool,

       0        // eod
};

void WriteBlocksShutdownTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WriteBlocksShutdownTask *_t = static_cast<WriteBlocksShutdownTask *>(_o);
        switch (_id) {
        case 0: { bool _r = _t->execute();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject WriteBlocksShutdownTask::staticMetaObject = {
    { &AbstractShutDownTask::staticMetaObject, qt_meta_stringdata_WriteBlocksShutdownTask.data,
      qt_meta_data_WriteBlocksShutdownTask,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *WriteBlocksShutdownTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WriteBlocksShutdownTask::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_WriteBlocksShutdownTask.stringdata))
        return static_cast<void*>(const_cast< WriteBlocksShutdownTask*>(this));
    return AbstractShutDownTask::qt_metacast(_clname);
}

int WriteBlocksShutdownTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractShutDownTask::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
