/****************************************************************************
** Meta object code from reading C++ file 'vsdoptionpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vsdoptionpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vsdoptionpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VSDOptionPanel_t {
    QByteArrayData data[5];
    char stringdata[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSDOptionPanel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSDOptionPanel_t qt_meta_stringdata_VSDOptionPanel = {
    {
QT_MOC_LITERAL(0, 0, 14), // "VSDOptionPanel"
QT_MOC_LITERAL(1, 15, 20), // "opsTrainSelectAction"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 12), // "ActionEvent*"
QT_MOC_LITERAL(4, 50, 1) // "e"

    },
    "VSDOptionPanel\0opsTrainSelectAction\0"
    "\0ActionEvent*\0e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSDOptionPanel[] = {

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

void VSDOptionPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VSDOptionPanel *_t = static_cast<VSDOptionPanel *>(_o);
        switch (_id) {
        case 0: _t->opsTrainSelectAction((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 1: _t->opsTrainSelectAction(); break;
        default: ;
        }
    }
}

const QMetaObject VSDOptionPanel::staticMetaObject = {
    { &JmriPanel::staticMetaObject, qt_meta_stringdata_VSDOptionPanel.data,
      qt_meta_data_VSDOptionPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VSDOptionPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSDOptionPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VSDOptionPanel.stringdata))
        return static_cast<void*>(const_cast< VSDOptionPanel*>(this));
    return JmriPanel::qt_metacast(_clname);
}

int VSDOptionPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = JmriPanel::qt_metacall(_c, _id, _a);
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
