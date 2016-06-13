/****************************************************************************
** Meta object code from reading C++ file 'guiutilbase.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "guiutilbase.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guiutilbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GuiUtilBase_t {
    QByteArrayData data[1];
    char stringdata[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GuiUtilBase_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GuiUtilBase_t qt_meta_stringdata_GuiUtilBase = {
    {
QT_MOC_LITERAL(0, 0, 11) // "GuiUtilBase"

    },
    "GuiUtilBase"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GuiUtilBase[] = {

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

void GuiUtilBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject GuiUtilBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GuiUtilBase.data,
      qt_meta_data_GuiUtilBase,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GuiUtilBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GuiUtilBase::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GuiUtilBase.stringdata))
        return static_cast<void*>(const_cast< GuiUtilBase*>(this));
    return QObject::qt_metacast(_clname);
}

int GuiUtilBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_CallingAbstractAction_t {
    QByteArrayData data[5];
    char stringdata[54];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CallingAbstractAction_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CallingAbstractAction_t qt_meta_stringdata_CallingAbstractAction = {
    {
QT_MOC_LITERAL(0, 0, 21), // "CallingAbstractAction"
QT_MOC_LITERAL(1, 22, 15), // "actionPerformed"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 12), // "ActionEvent*"
QT_MOC_LITERAL(4, 52, 1) // "e"

    },
    "CallingAbstractAction\0actionPerformed\0"
    "\0ActionEvent*\0e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CallingAbstractAction[] = {

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
       1,    0,   27,    2, 0x2a /* Public | MethodCloned */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void CallingAbstractAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CallingAbstractAction *_t = static_cast<CallingAbstractAction *>(_o);
        switch (_id) {
        case 0: _t->actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 1: _t->actionPerformed(); break;
        default: ;
        }
    }
}

const QMetaObject CallingAbstractAction::staticMetaObject = {
    { &AbstractAction::staticMetaObject, qt_meta_stringdata_CallingAbstractAction.data,
      qt_meta_data_CallingAbstractAction,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CallingAbstractAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CallingAbstractAction::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CallingAbstractAction.stringdata))
        return static_cast<void*>(const_cast< CallingAbstractAction*>(this));
    return AbstractAction::qt_metacast(_clname);
}

int CallingAbstractAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractAction::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_GUAbstractAction_t {
    QByteArrayData data[5];
    char stringdata[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GUAbstractAction_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GUAbstractAction_t qt_meta_stringdata_GUAbstractAction = {
    {
QT_MOC_LITERAL(0, 0, 16), // "GUAbstractAction"
QT_MOC_LITERAL(1, 17, 15), // "actionPerformed"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 12), // "ActionEvent*"
QT_MOC_LITERAL(4, 47, 1) // "e"

    },
    "GUAbstractAction\0actionPerformed\0\0"
    "ActionEvent*\0e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GUAbstractAction[] = {

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
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void GUAbstractAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GUAbstractAction *_t = static_cast<GUAbstractAction *>(_o);
        switch (_id) {
        case 0: _t->actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject GUAbstractAction::staticMetaObject = {
    { &AbstractAction::staticMetaObject, qt_meta_stringdata_GUAbstractAction.data,
      qt_meta_data_GUAbstractAction,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *GUAbstractAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GUAbstractAction::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_GUAbstractAction.stringdata))
        return static_cast<void*>(const_cast< GUAbstractAction*>(this));
    return AbstractAction::qt_metacast(_clname);
}

int GUAbstractAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractAction::qt_metacall(_c, _id, _a);
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
