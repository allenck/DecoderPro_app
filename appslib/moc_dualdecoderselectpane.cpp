/****************************************************************************
** Meta object code from reading C++ file 'dualdecoderselectpane.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dualdecoderselectpane.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dualdecoderselectpane.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DualDecoderSelectPane_t {
    QByteArrayData data[10];
    char stringdata[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DualDecoderSelectPane_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DualDecoderSelectPane_t qt_meta_stringdata_DualDecoderSelectPane = {
    {
QT_MOC_LITERAL(0, 0, 21), // "DualDecoderSelectPane"
QT_MOC_LITERAL(1, 22, 18), // "programmingOpReply"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 5), // "value"
QT_MOC_LITERAL(4, 48, 7), // "retcode"
QT_MOC_LITERAL(5, 56, 6), // "search"
QT_MOC_LITERAL(6, 63, 5), // "reset"
QT_MOC_LITERAL(7, 69, 6), // "doInit"
QT_MOC_LITERAL(8, 76, 6), // "select"
QT_MOC_LITERAL(9, 83, 6) // "number"

    },
    "DualDecoderSelectPane\0programmingOpReply\0"
    "\0value\0retcode\0search\0reset\0doInit\0"
    "select\0number"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DualDecoderSelectPane[] = {

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
       1,    2,   39,    2, 0x0a /* Public */,
       5,    0,   44,    2, 0x08 /* Private */,
       6,    0,   45,    2, 0x08 /* Private */,
       7,    0,   46,    2, 0x08 /* Private */,
       8,    1,   47,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void DualDecoderSelectPane::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DualDecoderSelectPane *_t = static_cast<DualDecoderSelectPane *>(_o);
        switch (_id) {
        case 0: _t->programmingOpReply((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->search(); break;
        case 2: _t->reset(); break;
        case 3: _t->doInit(); break;
        case 4: _t->select((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject DualDecoderSelectPane::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DualDecoderSelectPane.data,
      qt_meta_data_DualDecoderSelectPane,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DualDecoderSelectPane::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DualDecoderSelectPane::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DualDecoderSelectPane.stringdata))
        return static_cast<void*>(const_cast< DualDecoderSelectPane*>(this));
    return QWidget::qt_metacast(_clname);
}

int DualDecoderSelectPane::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
