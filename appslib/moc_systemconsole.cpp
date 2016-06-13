/****************************************************************************
** Meta object code from reading C++ file 'systemconsole.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "systemconsole.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'systemconsole.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SystemConsole_t {
    QByteArrayData data[13];
    char stringdata[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SystemConsole_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SystemConsole_t qt_meta_stringdata_SystemConsole = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SystemConsole"
QT_MOC_LITERAL(1, 14, 15), // "On_copy_clicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 16), // "On_close_clicked"
QT_MOC_LITERAL(4, 48, 21), // "On_autoScroll_toggled"
QT_MOC_LITERAL(5, 70, 22), // "On_alwaysOnTop_toggled"
QT_MOC_LITERAL(6, 93, 14), // "On_contextMenu"
QT_MOC_LITERAL(7, 108, 11), // "On_wrapLine"
QT_MOC_LITERAL(8, 120, 11), // "On_wrapWord"
QT_MOC_LITERAL(9, 132, 13), // "On_appendText"
QT_MOC_LITERAL(10, 146, 9), // "setScheme"
QT_MOC_LITERAL(11, 156, 5), // "which"
QT_MOC_LITERAL(12, 162, 19) // "On_setWrapStyleNone"

    },
    "SystemConsole\0On_copy_clicked\0\0"
    "On_close_clicked\0On_autoScroll_toggled\0"
    "On_alwaysOnTop_toggled\0On_contextMenu\0"
    "On_wrapLine\0On_wrapWord\0On_appendText\0"
    "setScheme\0which\0On_setWrapStyleNone"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SystemConsole[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    1,   66,    2, 0x0a /* Public */,
       5,    1,   69,    2, 0x0a /* Public */,
       6,    1,   72,    2, 0x0a /* Public */,
       7,    0,   75,    2, 0x0a /* Public */,
       8,    0,   76,    2, 0x0a /* Public */,
       9,    1,   77,    2, 0x0a /* Public */,
      10,    1,   80,    2, 0x0a /* Public */,
      12,    0,   83,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,

       0        // eod
};

void SystemConsole::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SystemConsole *_t = static_cast<SystemConsole *>(_o);
        switch (_id) {
        case 0: _t->On_copy_clicked(); break;
        case 1: _t->On_close_clicked(); break;
        case 2: _t->On_autoScroll_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->On_alwaysOnTop_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->On_contextMenu((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 5: _t->On_wrapLine(); break;
        case 6: _t->On_wrapWord(); break;
        case 7: _t->On_appendText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->setScheme((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->On_setWrapStyleNone(); break;
        default: ;
        }
    }
}

const QMetaObject SystemConsole::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SystemConsole.data,
      qt_meta_data_SystemConsole,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SystemConsole::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SystemConsole::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SystemConsole.stringdata))
        return static_cast<void*>(const_cast< SystemConsole*>(this));
    return QObject::qt_metacast(_clname);
}

int SystemConsole::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
