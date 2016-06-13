/****************************************************************************
** Meta object code from reading C++ file 'routeedittablemodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/routeedittablemodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'routeedittablemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__RouteEditTableModel_t {
    QByteArrayData data[7];
    char stringdata[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__RouteEditTableModel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__RouteEditTableModel_t qt_meta_stringdata_Operations__RouteEditTableModel = {
    {
QT_MOC_LITERAL(0, 0, 31), // "Operations::RouteEditTableModel"
QT_MOC_LITERAL(1, 32, 14), // "propertyChange"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(4, 69, 1), // "e"
QT_MOC_LITERAL(5, 71, 21), // "on_okayButton_clicked"
QT_MOC_LITERAL(6, 93, 23) // "on_cancelButton_clicked"

    },
    "Operations::RouteEditTableModel\0"
    "propertyChange\0\0PropertyChangeEvent*\0"
    "e\0on_okayButton_clicked\0on_cancelButton_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__RouteEditTableModel[] = {

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
       5,    0,   32,    2, 0x0a /* Public */,
       6,    0,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Operations::RouteEditTableModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RouteEditTableModel *_t = static_cast<RouteEditTableModel *>(_o);
        switch (_id) {
        case 0: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 1: _t->on_okayButton_clicked(); break;
        case 2: _t->on_cancelButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject Operations::RouteEditTableModel::staticMetaObject = {
    { &AbstractTableModel::staticMetaObject, qt_meta_stringdata_Operations__RouteEditTableModel.data,
      qt_meta_data_Operations__RouteEditTableModel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::RouteEditTableModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::RouteEditTableModel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__RouteEditTableModel.stringdata))
        return static_cast<void*>(const_cast< RouteEditTableModel*>(this));
    return AbstractTableModel::qt_metacast(_clname);
}

int Operations::RouteEditTableModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractTableModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_Operations__RETComboBoxDelegate_t {
    QByteArrayData data[1];
    char stringdata[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__RETComboBoxDelegate_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__RETComboBoxDelegate_t qt_meta_stringdata_Operations__RETComboBoxDelegate = {
    {
QT_MOC_LITERAL(0, 0, 31) // "Operations::RETComboBoxDelegate"

    },
    "Operations::RETComboBoxDelegate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__RETComboBoxDelegate[] = {

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

void Operations::RETComboBoxDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Operations::RETComboBoxDelegate::staticMetaObject = {
    { &QStyledItemDelegate::staticMetaObject, qt_meta_stringdata_Operations__RETComboBoxDelegate.data,
      qt_meta_data_Operations__RETComboBoxDelegate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::RETComboBoxDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::RETComboBoxDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__RETComboBoxDelegate.stringdata))
        return static_cast<void*>(const_cast< RETComboBoxDelegate*>(this));
    return QStyledItemDelegate::qt_metacast(_clname);
}

int Operations::RETComboBoxDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStyledItemDelegate::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
