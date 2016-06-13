/****************************************************************************
** Meta object code from reading C++ file 'trackroadeditframe.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/trackroadeditframe.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trackroadeditframe.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__TrackRoadEditFrame_t {
    QByteArrayData data[16];
    char stringdata[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__TrackRoadEditFrame_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__TrackRoadEditFrame_t qt_meta_stringdata_Operations__TrackRoadEditFrame = {
    {
QT_MOC_LITERAL(0, 0, 30), // "Operations::TrackRoadEditFrame"
QT_MOC_LITERAL(1, 31, 14), // "propertyChange"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(4, 68, 1), // "e"
QT_MOC_LITERAL(5, 70, 14), // "initComponents"
QT_MOC_LITERAL(6, 85, 9), // "Location*"
QT_MOC_LITERAL(7, 95, 8), // "location"
QT_MOC_LITERAL(8, 104, 6), // "Track*"
QT_MOC_LITERAL(9, 111, 5), // "track"
QT_MOC_LITERAL(10, 117, 21), // "buttonActionPerformed"
QT_MOC_LITERAL(11, 139, 8), // "QWidget*"
QT_MOC_LITERAL(12, 148, 2), // "ae"
QT_MOC_LITERAL(13, 151, 26), // "radioButtonActionPerformed"
QT_MOC_LITERAL(14, 178, 23), // "checkBoxActionPerformed"
QT_MOC_LITERAL(15, 202, 7) // "dispose"

    },
    "Operations::TrackRoadEditFrame\0"
    "propertyChange\0\0PropertyChangeEvent*\0"
    "e\0initComponents\0Location*\0location\0"
    "Track*\0track\0buttonActionPerformed\0"
    "QWidget*\0ae\0radioButtonActionPerformed\0"
    "checkBoxActionPerformed\0dispose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__TrackRoadEditFrame[] = {

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
       5,    2,   47,    2, 0x0a /* Public */,
      10,    1,   52,    2, 0x0a /* Public */,
      13,    1,   55,    2, 0x0a /* Public */,
      14,    1,   58,    2, 0x0a /* Public */,
      15,    0,   61,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,    7,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void Operations::TrackRoadEditFrame::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrackRoadEditFrame *_t = static_cast<TrackRoadEditFrame *>(_o);
        switch (_id) {
        case 0: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 1: _t->initComponents((*reinterpret_cast< Location*(*)>(_a[1])),(*reinterpret_cast< Track*(*)>(_a[2]))); break;
        case 2: _t->buttonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->radioButtonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 4: _t->checkBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 5: _t->dispose(); break;
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
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Operations::TrackRoadEditFrame::staticMetaObject = {
    { &OperationsFrame::staticMetaObject, qt_meta_stringdata_Operations__TrackRoadEditFrame.data,
      qt_meta_data_Operations__TrackRoadEditFrame,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::TrackRoadEditFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::TrackRoadEditFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__TrackRoadEditFrame.stringdata))
        return static_cast<void*>(const_cast< TrackRoadEditFrame*>(this));
    return OperationsFrame::qt_metacast(_clname);
}

int Operations::TrackRoadEditFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
