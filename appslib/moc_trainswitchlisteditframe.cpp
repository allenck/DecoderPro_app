/****************************************************************************
** Meta object code from reading C++ file 'trainswitchlisteditframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/trainswitchlisteditframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trainswitchlisteditframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__TrainSwitchListEditFrame_t {
    QByteArrayData data[14];
    char stringdata[257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__TrainSwitchListEditFrame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__TrainSwitchListEditFrame_t qt_meta_stringdata_Operations__TrainSwitchListEditFrame = {
    {
QT_MOC_LITERAL(0, 0, 36), // "Operations::TrainSwitchListEd..."
QT_MOC_LITERAL(1, 37, 14), // "propertyChange"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(4, 74, 1), // "e"
QT_MOC_LITERAL(5, 76, 21), // "buttonActionPerformed"
QT_MOC_LITERAL(6, 98, 8), // "QWidget*"
QT_MOC_LITERAL(7, 107, 2), // "ae"
QT_MOC_LITERAL(8, 110, 23), // "checkBoxActionPerformed"
QT_MOC_LITERAL(9, 134, 31), // "locationCheckBoxActionPerformed"
QT_MOC_LITERAL(10, 166, 28), // "commentButtonActionPerformed"
QT_MOC_LITERAL(11, 195, 12), // "ActionEvent*"
QT_MOC_LITERAL(12, 208, 24), // "changeLocationCheckboxes"
QT_MOC_LITERAL(13, 233, 23) // "comboBoxActionPerformed"

    },
    "Operations::TrainSwitchListEditFrame\0"
    "propertyChange\0\0PropertyChangeEvent*\0"
    "e\0buttonActionPerformed\0QWidget*\0ae\0"
    "checkBoxActionPerformed\0"
    "locationCheckBoxActionPerformed\0"
    "commentButtonActionPerformed\0ActionEvent*\0"
    "changeLocationCheckboxes\0"
    "comboBoxActionPerformed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__TrainSwitchListEditFrame[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x0a /* Public */,
       5,    1,   57,    2, 0x0a /* Public */,
       8,    1,   60,    2, 0x0a /* Public */,
       9,    1,   63,    2, 0x0a /* Public */,
      10,    1,   66,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x2a /* Public | MethodCloned */,
      12,    1,   70,    2, 0x08 /* Private */,
      13,    1,   73,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void, 0x80000000 | 11,    7,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void Operations::TrainSwitchListEditFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrainSwitchListEditFrame *_t = static_cast<TrainSwitchListEditFrame *>(_o);
        switch (_id) {
        case 0: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 1: _t->buttonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->checkBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->locationCheckBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 4: _t->commentButtonActionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 5: _t->commentButtonActionPerformed(); break;
        case 6: _t->changeLocationCheckboxes((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 7: _t->comboBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
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
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Operations::TrainSwitchListEditFrame::staticMetaObject = {
    { &OperationsFrame::staticMetaObject, qt_meta_stringdata_Operations__TrainSwitchListEditFrame.data,
      qt_meta_data_Operations__TrainSwitchListEditFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::TrainSwitchListEditFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::TrainSwitchListEditFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__TrainSwitchListEditFrame.stringdata))
        return static_cast<void*>(const_cast< TrainSwitchListEditFrame*>(this));
    return OperationsFrame::qt_metacast(_clname);
}

int Operations::TrainSwitchListEditFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OperationsFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
struct qt_meta_stringdata_Operations__TrainSwitchListCommentFrame_t {
    QByteArrayData data[5];
    char stringdata[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__TrainSwitchListCommentFrame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__TrainSwitchListCommentFrame_t qt_meta_stringdata_Operations__TrainSwitchListCommentFrame = {
    {
QT_MOC_LITERAL(0, 0, 39), // "Operations::TrainSwitchListCo..."
QT_MOC_LITERAL(1, 40, 21), // "buttonActionPerformed"
QT_MOC_LITERAL(2, 62, 0), // ""
QT_MOC_LITERAL(3, 63, 8), // "QWidget*"
QT_MOC_LITERAL(4, 72, 2) // "ae"

    },
    "Operations::TrainSwitchListCommentFrame\0"
    "buttonActionPerformed\0\0QWidget*\0ae"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__TrainSwitchListCommentFrame[] = {

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

void Operations::TrainSwitchListCommentFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrainSwitchListCommentFrame *_t = static_cast<TrainSwitchListCommentFrame *>(_o);
        switch (_id) {
        case 0: _t->buttonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
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
        }
    }
}

const QMetaObject Operations::TrainSwitchListCommentFrame::staticMetaObject = {
    { &OperationsFrame::staticMetaObject, qt_meta_stringdata_Operations__TrainSwitchListCommentFrame.data,
      qt_meta_data_Operations__TrainSwitchListCommentFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::TrainSwitchListCommentFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::TrainSwitchListCommentFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__TrainSwitchListCommentFrame.stringdata))
        return static_cast<void*>(const_cast< TrainSwitchListCommentFrame*>(this));
    return OperationsFrame::qt_metacast(_clname);
}

int Operations::TrainSwitchListCommentFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OperationsFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
