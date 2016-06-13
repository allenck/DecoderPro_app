/****************************************************************************
** Meta object code from reading C++ file 'systemconsoleconfigpanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "systemconsoleconfigpanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'systemconsoleconfigpanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SystemConsoleConfigPanel_t {
    QByteArrayData data[7];
    char stringdata[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SystemConsoleConfigPanel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SystemConsoleConfigPanel_t qt_meta_stringdata_SystemConsoleConfigPanel = {
    {
QT_MOC_LITERAL(0, 0, 24), // "SystemConsoleConfigPanel"
QT_MOC_LITERAL(1, 25, 10), // "On_Schemes"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 13), // "On_fontFamily"
QT_MOC_LITERAL(4, 51, 11), // "On_fontSize"
QT_MOC_LITERAL(5, 63, 12), // "On_wrapStyle"
QT_MOC_LITERAL(6, 76, 11) // "doFontStyle"

    },
    "SystemConsoleConfigPanel\0On_Schemes\0"
    "\0On_fontFamily\0On_fontSize\0On_wrapStyle\0"
    "doFontStyle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SystemConsoleConfigPanel[] = {

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
       3,    1,   42,    2, 0x0a /* Public */,
       4,    1,   45,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       6,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void SystemConsoleConfigPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SystemConsoleConfigPanel *_t = static_cast<SystemConsoleConfigPanel *>(_o);
        switch (_id) {
        case 0: _t->On_Schemes((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->On_fontFamily((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->On_fontSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->On_wrapStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->doFontStyle(); break;
        default: ;
        }
    }
}

const QMetaObject SystemConsoleConfigPanel::staticMetaObject = {
    { &PreferencesPanel::staticMetaObject, qt_meta_stringdata_SystemConsoleConfigPanel.data,
      qt_meta_data_SystemConsoleConfigPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SystemConsoleConfigPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SystemConsoleConfigPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SystemConsoleConfigPanel.stringdata))
        return static_cast<void*>(const_cast< SystemConsoleConfigPanel*>(this));
    return PreferencesPanel::qt_metacast(_clname);
}

int SystemConsoleConfigPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = PreferencesPanel::qt_metacall(_c, _id, _a);
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
