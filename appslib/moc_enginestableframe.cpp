/****************************************************************************
** Meta object code from reading C++ file 'enginestableframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/enginestableframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'enginestableframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__EnginesTableFrame_t {
    QByteArrayData data[10];
    char stringdata[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__EnginesTableFrame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__EnginesTableFrame_t qt_meta_stringdata_Operations__EnginesTableFrame = {
    {
QT_MOC_LITERAL(0, 0, 29), // "Operations::EnginesTableFrame"
QT_MOC_LITERAL(1, 30, 17), // "addButton_clicked"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 14), // "propertyChange"
QT_MOC_LITERAL(4, 64, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(5, 85, 1), // "e"
QT_MOC_LITERAL(6, 87, 26), // "radioButtonActionPerformed"
QT_MOC_LITERAL(7, 114, 8), // "QWidget*"
QT_MOC_LITERAL(8, 123, 6), // "source"
QT_MOC_LITERAL(9, 130, 21) // "buttonActionPerformed"

    },
    "Operations::EnginesTableFrame\0"
    "addButton_clicked\0\0propertyChange\0"
    "PropertyChangeEvent*\0e\0"
    "radioButtonActionPerformed\0QWidget*\0"
    "source\0buttonActionPerformed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__EnginesTableFrame[] = {

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
       1,    0,   34,    2, 0x0a /* Public */,
       3,    1,   35,    2, 0x0a /* Public */,
       6,    1,   38,    2, 0x0a /* Public */,
       9,    1,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void Operations::EnginesTableFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EnginesTableFrame *_t = static_cast<EnginesTableFrame *>(_o);
        switch (_id) {
        case 0: _t->addButton_clicked(); break;
        case 1: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 2: _t->radioButtonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->buttonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
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

const QMetaObject Operations::EnginesTableFrame::staticMetaObject = {
    { &OperationsFrame::staticMetaObject, qt_meta_stringdata_Operations__EnginesTableFrame.data,
      qt_meta_data_Operations__EnginesTableFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::EnginesTableFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::EnginesTableFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__EnginesTableFrame.stringdata))
        return static_cast<void*>(const_cast< EnginesTableFrame*>(this));
    return OperationsFrame::qt_metacast(_clname);
}

int Operations::EnginesTableFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
