/****************************************************************************
** Meta object code from reading C++ file 'showcarsintrainframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/showcarsintrainframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'showcarsintrainframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__ShowCarsInTrainFrame_t {
    QByteArrayData data[5];
    char stringdata[72];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__ShowCarsInTrainFrame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__ShowCarsInTrainFrame_t qt_meta_stringdata_Operations__ShowCarsInTrainFrame = {
    {
QT_MOC_LITERAL(0, 0, 32), // "Operations::ShowCarsInTrainFrame"
QT_MOC_LITERAL(1, 33, 14), // "propertyChange"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(4, 70, 1) // "e"

    },
    "Operations::ShowCarsInTrainFrame\0"
    "propertyChange\0\0PropertyChangeEvent*\0"
    "e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__ShowCarsInTrainFrame[] = {

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

void Operations::ShowCarsInTrainFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShowCarsInTrainFrame *_t = static_cast<ShowCarsInTrainFrame *>(_o);
        switch (_id) {
        case 0: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Operations::ShowCarsInTrainFrame::staticMetaObject = {
    { &OperationsFrame::staticMetaObject, qt_meta_stringdata_Operations__ShowCarsInTrainFrame.data,
      qt_meta_data_Operations__ShowCarsInTrainFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::ShowCarsInTrainFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::ShowCarsInTrainFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__ShowCarsInTrainFrame.stringdata))
        return static_cast<void*>(const_cast< ShowCarsInTrainFrame*>(this));
    return OperationsFrame::qt_metacast(_clname);
}

int Operations::ShowCarsInTrainFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OperationsFrame::qt_metacall(_c, _id, _a);
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
