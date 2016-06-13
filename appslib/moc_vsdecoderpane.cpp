/****************************************************************************
** Meta object code from reading C++ file 'vsdecoderpane.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vsdecoderpane.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vsdecoderpane.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VSDecoderPane_t {
    QByteArrayData data[11];
    char stringdata[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSDecoderPane_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSDecoderPane_t qt_meta_stringdata_VSDecoderPane = {
    {
QT_MOC_LITERAL(0, 0, 13), // "VSDecoderPane"
QT_MOC_LITERAL(1, 14, 19), // "notifyProperyChange"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(4, 56, 17), // "muteButtonPressed"
QT_MOC_LITERAL(5, 74, 12), // "ActionEvent*"
QT_MOC_LITERAL(6, 87, 1), // "e"
QT_MOC_LITERAL(7, 89, 12), // "volumeChange"
QT_MOC_LITERAL(8, 102, 12), // "ChangeEvent*"
QT_MOC_LITERAL(9, 115, 18), // "decoderEventAction"
QT_MOC_LITERAL(10, 134, 15) // "VSDecoderEvent*"

    },
    "VSDecoderPane\0notifyProperyChange\0\0"
    "PropertyChangeEvent*\0muteButtonPressed\0"
    "ActionEvent*\0e\0volumeChange\0ChangeEvent*\0"
    "decoderEventAction\0VSDecoderEvent*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSDecoderPane[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   47,    2, 0x0a /* Public */,
       4,    0,   50,    2, 0x2a /* Public | MethodCloned */,
       7,    1,   51,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x2a /* Public | MethodCloned */,
       9,    1,   55,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    6,

       0        // eod
};

void VSDecoderPane::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VSDecoderPane *_t = static_cast<VSDecoderPane *>(_o);
        switch (_id) {
        case 0: _t->notifyProperyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 1: _t->muteButtonPressed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 2: _t->muteButtonPressed(); break;
        case 3: _t->volumeChange((*reinterpret_cast< ChangeEvent*(*)>(_a[1]))); break;
        case 4: _t->volumeChange(); break;
        case 5: _t->decoderEventAction((*reinterpret_cast< VSDecoderEvent*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VSDecoderPane::*_t)(PropertyChangeEvent * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VSDecoderPane::notifyProperyChange)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject VSDecoderPane::staticMetaObject = {
    { &JmriPanel::staticMetaObject, qt_meta_stringdata_VSDecoderPane.data,
      qt_meta_data_VSDecoderPane,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VSDecoderPane::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSDecoderPane::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VSDecoderPane.stringdata))
        return static_cast<void*>(const_cast< VSDecoderPane*>(this));
    return JmriPanel::qt_metacast(_clname);
}

int VSDecoderPane::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = JmriPanel::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void VSDecoderPane::notifyProperyChange(PropertyChangeEvent * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
