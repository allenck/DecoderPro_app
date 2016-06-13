/****************************************************************************
** Meta object code from reading C++ file 'schedulestablemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/schedulestablemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'schedulestablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__SchedulesTableModel_t {
    QByteArrayData data[5];
    char stringdata[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__SchedulesTableModel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__SchedulesTableModel_t qt_meta_stringdata_Operations__SchedulesTableModel = {
    {
QT_MOC_LITERAL(0, 0, 31), // "Operations::SchedulesTableModel"
QT_MOC_LITERAL(1, 32, 14), // "propertyChange"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(4, 69, 1) // "e"

    },
    "Operations::SchedulesTableModel\0"
    "propertyChange\0\0PropertyChangeEvent*\0"
    "e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__SchedulesTableModel[] = {

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

void Operations::SchedulesTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SchedulesTableModel *_t = static_cast<SchedulesTableModel *>(_o);
        switch (_id) {
        case 0: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Operations::SchedulesTableModel::staticMetaObject = {
    { &AbstractTableModel::staticMetaObject, qt_meta_stringdata_Operations__SchedulesTableModel.data,
      qt_meta_data_Operations__SchedulesTableModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::SchedulesTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::SchedulesTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__SchedulesTableModel.stringdata))
        return static_cast<void*>(const_cast< SchedulesTableModel*>(this));
    return AbstractTableModel::qt_metacast(_clname);
}

int Operations::SchedulesTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractTableModel::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_Operations__STMSComboBoxDelegate_t {
    QByteArrayData data[1];
    char stringdata[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__STMSComboBoxDelegate_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__STMSComboBoxDelegate_t qt_meta_stringdata_Operations__STMSComboBoxDelegate = {
    {
QT_MOC_LITERAL(0, 0, 32) // "Operations::STMSComboBoxDelegate"

    },
    "Operations::STMSComboBoxDelegate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__STMSComboBoxDelegate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Operations::STMSComboBoxDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Operations::STMSComboBoxDelegate::staticMetaObject = {
    { &QStyledItemDelegate::staticMetaObject, qt_meta_stringdata_Operations__STMSComboBoxDelegate.data,
      qt_meta_data_Operations__STMSComboBoxDelegate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::STMSComboBoxDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::STMSComboBoxDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__STMSComboBoxDelegate.stringdata))
        return static_cast<void*>(const_cast< STMSComboBoxDelegate*>(this));
    return QStyledItemDelegate::qt_metacast(_clname);
}

int Operations::STMSComboBoxDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
