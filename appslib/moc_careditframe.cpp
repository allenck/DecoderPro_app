/****************************************************************************
** Meta object code from reading C++ file 'careditframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/careditframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'careditframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__CarEditFrame_t {
    QByteArrayData data[10];
    char stringdata[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__CarEditFrame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__CarEditFrame_t qt_meta_stringdata_Operations__CarEditFrame = {
    {
QT_MOC_LITERAL(0, 0, 24), // "Operations::CarEditFrame"
QT_MOC_LITERAL(1, 25, 14), // "propertyChange"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(4, 62, 1), // "e"
QT_MOC_LITERAL(5, 64, 25), // "buttonEditActionPerformed"
QT_MOC_LITERAL(6, 90, 8), // "QWidget*"
QT_MOC_LITERAL(7, 99, 2), // "ae"
QT_MOC_LITERAL(8, 102, 21), // "buttonActionPerformed"
QT_MOC_LITERAL(9, 124, 23) // "comboBoxActionPerformed"

    },
    "Operations::CarEditFrame\0propertyChange\0"
    "\0PropertyChangeEvent*\0e\0"
    "buttonEditActionPerformed\0QWidget*\0"
    "ae\0buttonActionPerformed\0"
    "comboBoxActionPerformed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__CarEditFrame[] = {

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
       5,    1,   37,    2, 0x0a /* Public */,
       8,    1,   40,    2, 0x0a /* Public */,
       9,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void Operations::CarEditFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CarEditFrame *_t = static_cast<CarEditFrame *>(_o);
        switch (_id) {
        case 0: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 1: _t->buttonEditActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->buttonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->comboBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
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
        }
    }
}

const QMetaObject Operations::CarEditFrame::staticMetaObject = {
    { &OperationsFrame::staticMetaObject, qt_meta_stringdata_Operations__CarEditFrame.data,
      qt_meta_data_Operations__CarEditFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::CarEditFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::CarEditFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__CarEditFrame.stringdata))
        return static_cast<void*>(const_cast< CarEditFrame*>(this));
    return OperationsFrame::qt_metacast(_clname);
}

int Operations::CarEditFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OperationsFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
