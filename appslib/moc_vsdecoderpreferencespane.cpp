/****************************************************************************
** Meta object code from reading C++ file 'vsdecoderpreferencespane.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vsdecoderpreferencespane.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vsdecoderpreferencespane.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VSDecoderPreferencesPane_t {
    QByteArrayData data[12];
    char stringdata[221];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VSDecoderPreferencesPane_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VSDecoderPreferencesPane_t qt_meta_stringdata_VSDecoderPreferencesPane = {
    {
QT_MOC_LITERAL(0, 0, 24), // "VSDecoderPreferencesPane"
QT_MOC_LITERAL(1, 25, 16), // "checkConsistency"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 21), // "jbSaveActionPerformed"
QT_MOC_LITERAL(4, 65, 12), // "ActionEvent*"
QT_MOC_LITERAL(5, 78, 3), // "evt"
QT_MOC_LITERAL(6, 82, 14), // "propertyChange"
QT_MOC_LITERAL(7, 97, 20), // "PropertyChangeEvent*"
QT_MOC_LITERAL(8, 118, 27), // "jbPathBrowseActionPerformed"
QT_MOC_LITERAL(9, 146, 27), // "jbFileBrowseActionPerformed"
QT_MOC_LITERAL(10, 174, 22), // "jbApplyActionPerformed"
QT_MOC_LITERAL(11, 197, 23) // "jbCancelActionPerformed"

    },
    "VSDecoderPreferencesPane\0checkConsistency\0"
    "\0jbSaveActionPerformed\0ActionEvent*\0"
    "evt\0propertyChange\0PropertyChangeEvent*\0"
    "jbPathBrowseActionPerformed\0"
    "jbFileBrowseActionPerformed\0"
    "jbApplyActionPerformed\0jbCancelActionPerformed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VSDecoderPreferencesPane[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    1,   75,    2, 0x0a /* Public */,
       3,    0,   78,    2, 0x2a /* Public | MethodCloned */,
       6,    1,   79,    2, 0x0a /* Public */,
       8,    1,   82,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x28 /* Private | MethodCloned */,
       9,    1,   86,    2, 0x08 /* Private */,
       9,    0,   89,    2, 0x28 /* Private | MethodCloned */,
      10,    1,   90,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x28 /* Private | MethodCloned */,
      11,    1,   94,    2, 0x08 /* Private */,
      11,    0,   97,    2, 0x28 /* Private | MethodCloned */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    5,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,

       0        // eod
};

void VSDecoderPreferencesPane::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VSDecoderPreferencesPane *_t = static_cast<VSDecoderPreferencesPane *>(_o);
        switch (_id) {
        case 0: _t->checkConsistency(); break;
        case 1: _t->jbSaveActionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 2: _t->jbSaveActionPerformed(); break;
        case 3: _t->propertyChange((*reinterpret_cast< PropertyChangeEvent*(*)>(_a[1]))); break;
        case 4: _t->jbPathBrowseActionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 5: _t->jbPathBrowseActionPerformed(); break;
        case 6: _t->jbFileBrowseActionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 7: _t->jbFileBrowseActionPerformed(); break;
        case 8: _t->jbApplyActionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 9: _t->jbApplyActionPerformed(); break;
        case 10: _t->jbCancelActionPerformed((*reinterpret_cast< ActionEvent*(*)>(_a[1]))); break;
        case 11: _t->jbCancelActionPerformed(); break;
        default: ;
        }
    }
}

const QMetaObject VSDecoderPreferencesPane::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VSDecoderPreferencesPane.data,
      qt_meta_data_VSDecoderPreferencesPane,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VSDecoderPreferencesPane::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VSDecoderPreferencesPane::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VSDecoderPreferencesPane.stringdata))
        return static_cast<void*>(const_cast< VSDecoderPreferencesPane*>(this));
    return QWidget::qt_metacast(_clname);
}

int VSDecoderPreferencesPane::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
