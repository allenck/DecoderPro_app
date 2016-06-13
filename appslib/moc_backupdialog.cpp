/****************************************************************************
** Meta object code from reading C++ file 'backupdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/backupdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'backupdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__BackupDialog_t {
    QByteArrayData data[8];
    char stringdata[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__BackupDialog_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__BackupDialog_t qt_meta_stringdata_Operations__BackupDialog = {
    {
QT_MOC_LITERAL(0, 0, 24), // "Operations::BackupDialog"
QT_MOC_LITERAL(1, 25, 31), // "do_backupButton_actionPerformed"
QT_MOC_LITERAL(2, 57, 0), // ""
QT_MOC_LITERAL(3, 58, 12), // "ActionEvent*"
QT_MOC_LITERAL(4, 71, 1), // "e"
QT_MOC_LITERAL(5, 73, 31), // "do_cancelButton_actionPerformed"
QT_MOC_LITERAL(6, 105, 4), // "arg0"
QT_MOC_LITERAL(7, 110, 29) // "do_helpButton_actionPerformed"

    },
    "Operations::BackupDialog\0"
    "do_backupButton_actionPerformed\0\0"
    "ActionEvent*\0e\0do_cancelButton_actionPerformed\0"
    "arg0\0do_helpButton_actionPerformed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__BackupDialog[] = {

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
       1,    1,   44,    2, 0x09 /* Protected */,
       1,    0,   47,    2, 0x29 /* Protected | MethodCloned */,
       5,    1,   48,    2, 0x09 /* Protected */,
       5,    0,   51,    2, 0x29 /* Protected | MethodCloned */,
       7,    1,   52,    2, 0x09 /* Protected */,
       7,    0,   55,    2, 0x29 /* Protected | MethodCloned */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void Operations::BackupDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BackupDialog *_t = static_cast<BackupDialog *>(_o);
        switch (_id) {
        case 0: _t->do_backupButton_actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 1: _t->do_backupButton_actionPerformed(); break;
        case 2: _t->do_cancelButton_actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 3: _t->do_cancelButton_actionPerformed(); break;
        case 4: _t->do_helpButton_actionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 5: _t->do_helpButton_actionPerformed(); break;
        default: ;
        }
    }
}

const QMetaObject Operations::BackupDialog::staticMetaObject = {
    { &JDialog::staticMetaObject, qt_meta_stringdata_Operations__BackupDialog.data,
      qt_meta_data_Operations__BackupDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::BackupDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::BackupDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__BackupDialog.stringdata))
        return static_cast<void*>(const_cast< BackupDialog*>(this));
    return JDialog::qt_metacast(_clname);
}

int Operations::BackupDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = JDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
