/****************************************************************************
** Meta object code from reading C++ file 'printoptionpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/printoptionpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'printoptionpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__PrintOptionPanel_t {
    QByteArrayData data[7];
    char stringdata[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__PrintOptionPanel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__PrintOptionPanel_t qt_meta_stringdata_Operations__PrintOptionPanel = {
    {
QT_MOC_LITERAL(0, 0, 28), // "Operations::PrintOptionPanel"
QT_MOC_LITERAL(1, 29, 21), // "buttonActionPerformed"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 8), // "QWidget*"
QT_MOC_LITERAL(4, 61, 2), // "ae"
QT_MOC_LITERAL(5, 64, 23), // "checkBoxActionPerformed"
QT_MOC_LITERAL(6, 88, 23) // "comboBoxActionPerformed"

    },
    "Operations::PrintOptionPanel\0"
    "buttonActionPerformed\0\0QWidget*\0ae\0"
    "checkBoxActionPerformed\0comboBoxActionPerformed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__PrintOptionPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       5,    1,   32,    2, 0x0a /* Public */,
       6,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void Operations::PrintOptionPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PrintOptionPanel *_t = static_cast<PrintOptionPanel *>(_o);
        switch (_id) {
        case 0: _t->buttonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->checkBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->comboBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
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
        }
    }
}

const QMetaObject Operations::PrintOptionPanel::staticMetaObject = {
    { &OperationsPreferencesPanel::staticMetaObject, qt_meta_stringdata_Operations__PrintOptionPanel.data,
      qt_meta_data_Operations__PrintOptionPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::PrintOptionPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::PrintOptionPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__PrintOptionPanel.stringdata))
        return static_cast<void*>(const_cast< PrintOptionPanel*>(this));
    return OperationsPreferencesPanel::qt_metacast(_clname);
}

int Operations::PrintOptionPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OperationsPreferencesPanel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
