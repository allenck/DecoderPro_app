/****************************************************************************
** Meta object code from reading C++ file 'consisttoolaction.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "consisttoolaction.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'consisttoolaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ConsistToolAction_t {
    QByteArrayData data[10];
    char stringdata[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConsistToolAction_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConsistToolAction_t qt_meta_stringdata_ConsistToolAction = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ConsistToolAction"
QT_MOC_LITERAL(1, 18, 15), // "actionPerformed"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 12), // "ActionEvent*"
QT_MOC_LITERAL(4, 48, 1), // "e"
QT_MOC_LITERAL(5, 50, 6), // "parent"
QT_MOC_LITERAL(6, 57, 1), // "s"
QT_MOC_LITERAL(7, 59, 16), // "WindowInterface*"
QT_MOC_LITERAL(8, 76, 2), // "wi"
QT_MOC_LITERAL(9, 79, 1) // "i"

    },
    "ConsistToolAction\0actionPerformed\0\0"
    "ActionEvent*\0e\0parent\0s\0WindowInterface*\0"
    "wi\0i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConsistToolAction[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       5,   49, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       1,    0,   27,    2, 0x2a /* Public | MethodCloned */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // constructors: parameters
    0x80000000 | 2, QMetaType::QObjectStar,    5,
    0x80000000 | 2,
    0x80000000 | 2, QMetaType::QString, 0x80000000 | 7,    6,    8,
    0x80000000 | 2, QMetaType::QString, QMetaType::QIcon, 0x80000000 | 7,    6,    9,    8,
    0x80000000 | 2, QMetaType::QString, QMetaType::QObjectStar,    6,    5,

 // constructors: name, argc, parameters, tag, flags
       0,    1,   28,    2, 0x0e /* Public */,
       0,    0,   31,    2, 0x2e /* Public | MethodCloned */,
       0,    2,   32,    2, 0x0e /* Public */,
       0,    3,   37,    2, 0x0e /* Public */,
       0,    2,   44,    2, 0x0e /* Public */,

       0        // eod
};

void ConsistToolAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ConsistToolAction *_r = new ConsistToolAction((*reinterpret_cast< QObject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 1: { ConsistToolAction *_r = new ConsistToolAction();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 2: { ConsistToolAction *_r = new ConsistToolAction((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< WindowInterface*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 3: { ConsistToolAction *_r = new ConsistToolAction((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QIcon(*)>(_a[2])),(*reinterpret_cast< WindowInterface*(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 4: { ConsistToolAction *_r = new ConsistToolAction((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QObject*(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        ConsistToolAction *_t = static_cast<ConsistToolAction *>(_o);
        switch (_id) {
        case 0: _t->actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 1: _t->actionPerformed(); break;
        default: ;
        }
    }
}

const QMetaObject ConsistToolAction::staticMetaObject = {
    { &JmriAbstractAction::staticMetaObject, qt_meta_stringdata_ConsistToolAction.data,
      qt_meta_data_ConsistToolAction,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConsistToolAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConsistToolAction::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConsistToolAction.stringdata))
        return static_cast<void*>(const_cast< ConsistToolAction*>(this));
    return JmriAbstractAction::qt_metacast(_clname);
}

int ConsistToolAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = JmriAbstractAction::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
