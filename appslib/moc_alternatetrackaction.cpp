/****************************************************************************
** Meta object code from reading C++ file 'alternatetrackaction.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/alternatetrackaction.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'alternatetrackaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__AlternateTrackAction_t {
    QByteArrayData data[5];
    char stringdata[65];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__AlternateTrackAction_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__AlternateTrackAction_t qt_meta_stringdata_Operations__AlternateTrackAction = {
    {
QT_MOC_LITERAL(0, 0, 32), // "Operations::AlternateTrackAction"
QT_MOC_LITERAL(1, 33, 15), // "actionPerformed"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 12), // "ActionEvent*"
QT_MOC_LITERAL(4, 63, 1) // "e"

    },
    "Operations::AlternateTrackAction\0"
    "actionPerformed\0\0ActionEvent*\0e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__AlternateTrackAction[] = {

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

void Operations::AlternateTrackAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AlternateTrackAction *_t = static_cast<AlternateTrackAction *>(_o);
        switch (_id) {
        case 0: _t->actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 1: _t->actionPerformed(); break;
        default: ;
        }
    }
}

const QMetaObject Operations::AlternateTrackAction::staticMetaObject = {
    { &AbstractAction::staticMetaObject, qt_meta_stringdata_Operations__AlternateTrackAction.data,
      qt_meta_data_Operations__AlternateTrackAction,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::AlternateTrackAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::AlternateTrackAction::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__AlternateTrackAction.stringdata))
        return static_cast<void*>(const_cast< AlternateTrackAction*>(this));
    return AbstractAction::qt_metacast(_clname);
}

int Operations::AlternateTrackAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
