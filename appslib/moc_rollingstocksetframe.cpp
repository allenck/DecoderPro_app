/****************************************************************************
** Meta object code from reading C++ file 'rollingstocksetframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/rollingstocksetframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'rollingstocksetframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__RollingStockSetFrame_t {
    QByteArrayData data[11];
    char stringdata[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__RollingStockSetFrame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__RollingStockSetFrame_t qt_meta_stringdata_Operations__RollingStockSetFrame = {
    {
QT_MOC_LITERAL(0, 0, 32), // "Operations::RollingStockSetFrame"
QT_MOC_LITERAL(1, 33, 23), // "comboBoxActionPerformed"
QT_MOC_LITERAL(2, 57, 0), // ""
QT_MOC_LITERAL(3, 58, 8), // "QWidget*"
QT_MOC_LITERAL(4, 67, 2), // "ae"
QT_MOC_LITERAL(5, 70, 7), // "dispose"
QT_MOC_LITERAL(6, 78, 14), // "propertyChange"
QT_MOC_LITERAL(7, 93, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(8, 114, 1), // "e"
QT_MOC_LITERAL(9, 116, 23), // "checkBoxActionPerformed"
QT_MOC_LITERAL(10, 140, 21) // "buttonActionPerformed"

    },
    "Operations::RollingStockSetFrame\0"
    "comboBoxActionPerformed\0\0QWidget*\0ae\0"
    "dispose\0propertyChange\0PropertyChangeEvent*\0"
    "e\0checkBoxActionPerformed\0"
    "buttonActionPerformed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__RollingStockSetFrame[] = {

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
       5,    0,   42,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,
       9,    1,   46,    2, 0x0a /* Public */,
      10,    1,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void Operations::RollingStockSetFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RollingStockSetFrame *_t = static_cast<RollingStockSetFrame *>(_o);
        switch (_id) {
        case 0: _t->comboBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->dispose(); break;
        case 2: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 3: _t->checkBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 4: _t->buttonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
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

const QMetaObject Operations::RollingStockSetFrame::staticMetaObject = {
    { &OperationsFrame::staticMetaObject, qt_meta_stringdata_Operations__RollingStockSetFrame.data,
      qt_meta_data_Operations__RollingStockSetFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::RollingStockSetFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::RollingStockSetFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__RollingStockSetFrame.stringdata))
        return static_cast<void*>(const_cast< RollingStockSetFrame*>(this));
    return OperationsFrame::qt_metacast(_clname);
}

int Operations::RollingStockSetFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
