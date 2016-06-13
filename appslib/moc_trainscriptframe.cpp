/****************************************************************************
** Meta object code from reading C++ file 'trainscriptframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/trainscriptframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trainscriptframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__TrainScriptFrame_t {
    QByteArrayData data[9];
    char stringdata[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__TrainScriptFrame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__TrainScriptFrame_t qt_meta_stringdata_Operations__TrainScriptFrame = {
    {
QT_MOC_LITERAL(0, 0, 28), // "Operations::TrainScriptFrame"
QT_MOC_LITERAL(1, 29, 29), // "buttonActionRemoveBuildScript"
QT_MOC_LITERAL(2, 59, 0), // ""
QT_MOC_LITERAL(3, 60, 8), // "QWidget*"
QT_MOC_LITERAL(4, 69, 2), // "ae"
QT_MOC_LITERAL(5, 72, 21), // "buttonActionPerformed"
QT_MOC_LITERAL(6, 94, 34), // "buttonActionRemoveAfterBuildS..."
QT_MOC_LITERAL(7, 129, 28), // "buttonActionRemoveMoveScript"
QT_MOC_LITERAL(8, 158, 35) // "buttonActionRemoveTermination..."

    },
    "Operations::TrainScriptFrame\0"
    "buttonActionRemoveBuildScript\0\0QWidget*\0"
    "ae\0buttonActionPerformed\0"
    "buttonActionRemoveAfterBuildScript\0"
    "buttonActionRemoveMoveScript\0"
    "buttonActionRemoveTerminationScript"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__TrainScriptFrame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       5,    1,   42,    2, 0x0a /* Public */,
       6,    1,   45,    2, 0x0a /* Public */,
       7,    1,   48,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void Operations::TrainScriptFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrainScriptFrame *_t = static_cast<TrainScriptFrame *>(_o);
        switch (_id) {
        case 0: _t->buttonActionRemoveBuildScript((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->buttonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->buttonActionRemoveAfterBuildScript((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->buttonActionRemoveMoveScript((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 4: _t->buttonActionRemoveTerminationScript((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Operations::TrainScriptFrame::staticMetaObject = {
    { &OperationsFrame::staticMetaObject, qt_meta_stringdata_Operations__TrainScriptFrame.data,
      qt_meta_data_Operations__TrainScriptFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::TrainScriptFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::TrainScriptFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__TrainScriptFrame.stringdata))
        return static_cast<void*>(const_cast< TrainScriptFrame*>(this));
    return OperationsFrame::qt_metacast(_clname);
}

int Operations::TrainScriptFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OperationsFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
