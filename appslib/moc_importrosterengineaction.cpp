/****************************************************************************
** Meta object code from reading C++ file 'importrosterengineaction.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/importrosterengineaction.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'importrosterengineaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__ImportRosterEngineAction_t {
    QByteArrayData data[8];
    char stringdata[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__ImportRosterEngineAction_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__ImportRosterEngineAction_t qt_meta_stringdata_Operations__ImportRosterEngineAction = {
    {
QT_MOC_LITERAL(0, 0, 36), // "Operations::ImportRosterEngin..."
QT_MOC_LITERAL(1, 37, 15), // "actionPerformed"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 12), // "ActionEvent*"
QT_MOC_LITERAL(4, 67, 2), // "ae"
QT_MOC_LITERAL(5, 70, 10), // "onProgress"
QT_MOC_LITERAL(6, 81, 6), // "textId"
QT_MOC_LITERAL(7, 88, 10) // "onFinished"

    },
    "Operations::ImportRosterEngineAction\0"
    "actionPerformed\0\0ActionEvent*\0ae\0"
    "onProgress\0textId\0onFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__ImportRosterEngineAction[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       1,    0,   37,    2, 0x2a /* Public | MethodCloned */,
       5,    1,   38,    2, 0x0a /* Public */,
       7,    1,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Operations::ImportRosterEngineAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImportRosterEngineAction *_t = static_cast<ImportRosterEngineAction *>(_o);
        switch (_id) {
        case 0: _t->actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 1: _t->actionPerformed(); break;
        case 2: _t->onProgress((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->onFinished((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Operations::ImportRosterEngineAction::staticMetaObject = {
    { &AbstractAction::staticMetaObject, qt_meta_stringdata_Operations__ImportRosterEngineAction.data,
      qt_meta_data_Operations__ImportRosterEngineAction,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::ImportRosterEngineAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::ImportRosterEngineAction::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__ImportRosterEngineAction.stringdata))
        return static_cast<void*>(const_cast< ImportRosterEngineAction*>(this));
    return AbstractAction::qt_metacast(_clname);
}

int Operations::ImportRosterEngineAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
