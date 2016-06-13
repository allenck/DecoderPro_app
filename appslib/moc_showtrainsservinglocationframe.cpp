/****************************************************************************
** Meta object code from reading C++ file 'showtrainsservinglocationframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/showtrainsservinglocationframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'showtrainsservinglocationframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__ShowTrainsServingLocationFrame_t {
    QByteArrayData data[12];
    char stringdata[207];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__ShowTrainsServingLocationFrame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__ShowTrainsServingLocationFrame_t qt_meta_stringdata_Operations__ShowTrainsServingLocationFrame = {
    {
QT_MOC_LITERAL(0, 0, 42), // "Operations::ShowTrainsServing..."
QT_MOC_LITERAL(1, 43, 14), // "propertyChange"
QT_MOC_LITERAL(2, 58, 0), // ""
QT_MOC_LITERAL(3, 59, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(4, 80, 1), // "e"
QT_MOC_LITERAL(5, 82, 23), // "checkBoxActionPerformed"
QT_MOC_LITERAL(6, 106, 8), // "QWidget*"
QT_MOC_LITERAL(7, 115, 2), // "ae"
QT_MOC_LITERAL(8, 118, 23), // "comboBoxActionPerformed"
QT_MOC_LITERAL(9, 142, 7), // "dispose"
QT_MOC_LITERAL(10, 150, 26), // "addPropertyChangeAllTrains"
QT_MOC_LITERAL(11, 177, 29) // "removePropertyChangeAllTrains"

    },
    "Operations::ShowTrainsServingLocationFrame\0"
    "propertyChange\0\0PropertyChangeEvent*\0"
    "e\0checkBoxActionPerformed\0QWidget*\0"
    "ae\0comboBoxActionPerformed\0dispose\0"
    "addPropertyChangeAllTrains\0"
    "removePropertyChangeAllTrains"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__ShowTrainsServingLocationFrame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x0a /* Public */,
       5,    1,   47,    2, 0x0a /* Public */,
       8,    1,   50,    2, 0x0a /* Public */,
       9,    0,   53,    2, 0x0a /* Public */,
      10,    0,   54,    2, 0x0a /* Public */,
      11,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Operations::ShowTrainsServingLocationFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShowTrainsServingLocationFrame *_t = static_cast<ShowTrainsServingLocationFrame *>(_o);
        switch (_id) {
        case 0: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 1: _t->checkBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->comboBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->dispose(); break;
        case 4: _t->addPropertyChangeAllTrains(); break;
        case 5: _t->removePropertyChangeAllTrains(); break;
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
        }
    }
}

const QMetaObject Operations::ShowTrainsServingLocationFrame::staticMetaObject = {
    { &OperationsFrame::staticMetaObject, qt_meta_stringdata_Operations__ShowTrainsServingLocationFrame.data,
      qt_meta_data_Operations__ShowTrainsServingLocationFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::ShowTrainsServingLocationFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::ShowTrainsServingLocationFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__ShowTrainsServingLocationFrame.stringdata))
        return static_cast<void*>(const_cast< ShowTrainsServingLocationFrame*>(this));
    return OperationsFrame::qt_metacast(_clname);
}

int Operations::ShowTrainsServingLocationFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OperationsFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
