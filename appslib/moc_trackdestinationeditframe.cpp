/****************************************************************************
** Meta object code from reading C++ file 'trackdestinationeditframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/trackdestinationeditframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trackdestinationeditframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__TrackDestinationEditFrame_t {
    QByteArrayData data[12];
    char stringdata[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__TrackDestinationEditFrame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__TrackDestinationEditFrame_t qt_meta_stringdata_Operations__TrackDestinationEditFrame = {
    {
QT_MOC_LITERAL(0, 0, 37), // "Operations::TrackDestinationE..."
QT_MOC_LITERAL(1, 38, 14), // "propertyChange"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(4, 75, 1), // "e"
QT_MOC_LITERAL(5, 77, 21), // "buttonActionPerformed"
QT_MOC_LITERAL(6, 99, 8), // "QWidget*"
QT_MOC_LITERAL(7, 108, 2), // "ae"
QT_MOC_LITERAL(8, 111, 26), // "radioButtonActionPerformed"
QT_MOC_LITERAL(9, 138, 23), // "checkBoxActionPerformed"
QT_MOC_LITERAL(10, 162, 6), // "on_msg"
QT_MOC_LITERAL(11, 169, 3) // "msg"

    },
    "Operations::TrackDestinationEditFrame\0"
    "propertyChange\0\0PropertyChangeEvent*\0"
    "e\0buttonActionPerformed\0QWidget*\0ae\0"
    "radioButtonActionPerformed\0"
    "checkBoxActionPerformed\0on_msg\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__TrackDestinationEditFrame[] = {

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
       5,    1,   42,    2, 0x0a /* Public */,
       8,    1,   45,    2, 0x0a /* Public */,
       9,    1,   48,    2, 0x0a /* Public */,
      10,    1,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void Operations::TrackDestinationEditFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrackDestinationEditFrame *_t = static_cast<TrackDestinationEditFrame *>(_o);
        switch (_id) {
        case 0: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 1: _t->buttonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->radioButtonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->checkBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 4: _t->on_msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
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
        }
    }
}

const QMetaObject Operations::TrackDestinationEditFrame::staticMetaObject = {
    { &OperationsFrame::staticMetaObject, qt_meta_stringdata_Operations__TrackDestinationEditFrame.data,
      qt_meta_data_Operations__TrackDestinationEditFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::TrackDestinationEditFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::TrackDestinationEditFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__TrackDestinationEditFrame.stringdata))
        return static_cast<void*>(const_cast< TrackDestinationEditFrame*>(this));
    return OperationsFrame::qt_metacast(_clname);
}

int Operations::TrackDestinationEditFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
struct qt_meta_stringdata_Operations__CheckLocations_t {
    QByteArrayData data[5];
    char stringdata[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__CheckLocations_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__CheckLocations_t qt_meta_stringdata_Operations__CheckLocations = {
    {
QT_MOC_LITERAL(0, 0, 26), // "Operations::CheckLocations"
QT_MOC_LITERAL(1, 27, 8), // "finished"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 3), // "msg"
QT_MOC_LITERAL(4, 41, 7) // "process"

    },
    "Operations::CheckLocations\0finished\0"
    "\0msg\0process"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__CheckLocations[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    1,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void Operations::CheckLocations::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CheckLocations *_t = static_cast<CheckLocations *>(_o);
        switch (_id) {
        case 0: _t->finished(); break;
        case 1: _t->msg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->process(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CheckLocations::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CheckLocations::finished)) {
                *result = 0;
            }
        }
        {
            typedef void (CheckLocations::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CheckLocations::msg)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject Operations::CheckLocations::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Operations__CheckLocations.data,
      qt_meta_data_Operations__CheckLocations,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::CheckLocations::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::CheckLocations::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__CheckLocations.stringdata))
        return static_cast<void*>(const_cast< CheckLocations*>(this));
    return QObject::qt_metacast(_clname);
}

int Operations::CheckLocations::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Operations::CheckLocations::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void Operations::CheckLocations::msg(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
