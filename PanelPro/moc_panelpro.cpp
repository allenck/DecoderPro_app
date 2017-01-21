/****************************************************************************
** Meta object code from reading C++ file 'panelpro.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "panelpro.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'panelpro.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PanelPro_t {
    QByteArrayData data[3];
    char stringdata[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PanelPro_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PanelPro_t qt_meta_stringdata_PanelPro = {
    {
QT_MOC_LITERAL(0, 0, 8), // "PanelPro"
QT_MOC_LITERAL(1, 9, 10), // "handleQuit"
QT_MOC_LITERAL(2, 20, 0) // ""

    },
    "PanelPro\0handleQuit\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PanelPro[] = {

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
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void PanelPro::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PanelPro *_t = static_cast<PanelPro *>(_o);
        switch (_id) {
        case 0: _t->handleQuit(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject PanelPro::staticMetaObject = {
    { &Apps::staticMetaObject, qt_meta_stringdata_PanelPro.data,
      qt_meta_data_PanelPro,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PanelPro::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PanelPro::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PanelPro.stringdata))
        return static_cast<void*>(const_cast< PanelPro*>(this));
    return Apps::qt_metacast(_clname);
}

int PanelPro::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Apps::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_PPWindowListener_t {
    QByteArrayData data[1];
    char stringdata[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PPWindowListener_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PPWindowListener_t qt_meta_stringdata_PPWindowListener = {
    {
QT_MOC_LITERAL(0, 0, 16) // "PPWindowListener"

    },
    "PPWindowListener"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PPWindowListener[] = {

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

void PPWindowListener::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject PPWindowListener::staticMetaObject = {
    { &WindowListener::staticMetaObject, qt_meta_stringdata_PPWindowListener.data,
      qt_meta_data_PPWindowListener,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PPWindowListener::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PPWindowListener::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PPWindowListener.stringdata))
        return static_cast<void*>(const_cast< PPWindowListener*>(this));
    return WindowListener::qt_metacast(_clname);
}

int PPWindowListener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WindowListener::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
