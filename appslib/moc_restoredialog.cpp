/****************************************************************************
** Meta object code from reading C++ file 'restoredialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/restoredialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'restoredialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__RestoreDialog_t {
    QByteArrayData data[12];
    char stringdata[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__RestoreDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__RestoreDialog_t qt_meta_stringdata_Operations__RestoreDialog = {
    {
QT_MOC_LITERAL(0, 0, 25), // "Operations::RestoreDialog"
QT_MOC_LITERAL(1, 26, 46), // "do_automaticBackupsRadioButto..."
QT_MOC_LITERAL(2, 73, 0), // ""
QT_MOC_LITERAL(3, 74, 12), // "ActionEvent*"
QT_MOC_LITERAL(4, 87, 1), // "e"
QT_MOC_LITERAL(5, 89, 44), // "do_defaultBackupsRadioButton_..."
QT_MOC_LITERAL(6, 134, 31), // "do_cancelButton_actionPerformed"
QT_MOC_LITERAL(7, 166, 4), // "arg0"
QT_MOC_LITERAL(8, 171, 28), // "do_comboBox_itemStateChanged"
QT_MOC_LITERAL(9, 200, 10), // "ItemEvent*"
QT_MOC_LITERAL(10, 211, 29), // "do_helpButton_actionPerformed"
QT_MOC_LITERAL(11, 241, 32) // "do_restoreButton_actionPerformed"

    },
    "Operations::RestoreDialog\0"
    "do_automaticBackupsRadioButton_actionPerformed\0"
    "\0ActionEvent*\0e\0"
    "do_defaultBackupsRadioButton_actionPerformed\0"
    "do_cancelButton_actionPerformed\0arg0\0"
    "do_comboBox_itemStateChanged\0ItemEvent*\0"
    "do_helpButton_actionPerformed\0"
    "do_restoreButton_actionPerformed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__RestoreDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x09 /* Protected */,
       1,    0,   77,    2, 0x29 /* Protected | MethodCloned */,
       5,    1,   78,    2, 0x09 /* Protected */,
       5,    0,   81,    2, 0x29 /* Protected | MethodCloned */,
       6,    1,   82,    2, 0x09 /* Protected */,
       6,    0,   85,    2, 0x29 /* Protected | MethodCloned */,
       8,    1,   86,    2, 0x09 /* Protected */,
       8,    0,   89,    2, 0x29 /* Protected | MethodCloned */,
      10,    1,   90,    2, 0x09 /* Protected */,
      10,    0,   93,    2, 0x29 /* Protected | MethodCloned */,
      11,    1,   94,    2, 0x09 /* Protected */,
      11,    0,   97,    2, 0x29 /* Protected | MethodCloned */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void Operations::RestoreDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RestoreDialog *_t = static_cast<RestoreDialog *>(_o);
        switch (_id) {
        case 0: _t->do_automaticBackupsRadioButton_actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 1: _t->do_automaticBackupsRadioButton_actionPerformed(); break;
        case 2: _t->do_defaultBackupsRadioButton_actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 3: _t->do_defaultBackupsRadioButton_actionPerformed(); break;
        case 4: _t->do_cancelButton_actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 5: _t->do_cancelButton_actionPerformed(); break;
        case 6: _t->do_comboBox_itemStateChanged((*reinterpret_cast< ItemEvent*(*)>(_a[1]))); break;
        case 7: _t->do_comboBox_itemStateChanged(); break;
        case 8: _t->do_helpButton_actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 9: _t->do_helpButton_actionPerformed(); break;
        case 10: _t->do_restoreButton_actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 11: _t->do_restoreButton_actionPerformed(); break;
        default: ;
        }
    }
}

const QMetaObject Operations::RestoreDialog::staticMetaObject = {
    { &JDialog::staticMetaObject, qt_meta_stringdata_Operations__RestoreDialog.data,
      qt_meta_data_Operations__RestoreDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::RestoreDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::RestoreDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__RestoreDialog.stringdata))
        return static_cast<void*>(const_cast< RestoreDialog*>(this));
    return JDialog::qt_metacast(_clname);
}

int Operations::RestoreDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = JDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
