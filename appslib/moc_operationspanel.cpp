/****************************************************************************
** Meta object code from reading C++ file 'operationspanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "operations/operationspanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'operationspanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Operations__OperationsPanel_t {
    QByteArrayData data[19];
    char stringdata[284];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Operations__OperationsPanel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Operations__OperationsPanel_t qt_meta_stringdata_Operations__OperationsPanel = {
    {
QT_MOC_LITERAL(0, 0, 27), // "Operations::OperationsPanel"
QT_MOC_LITERAL(1, 28, 21), // "buttonActionPerformed"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 8), // "QWidget*"
QT_MOC_LITERAL(4, 60, 26), // "radioButtonActionPerformed"
QT_MOC_LITERAL(5, 87, 23), // "checkBoxActionPerformed"
QT_MOC_LITERAL(6, 111, 25), // "addSpinnerChangeListerner"
QT_MOC_LITERAL(7, 137, 9), // "QSpinBox*"
QT_MOC_LITERAL(8, 147, 1), // "s"
QT_MOC_LITERAL(9, 149, 18), // "spinnerChangeEvent"
QT_MOC_LITERAL(10, 168, 12), // "ChangeEvent*"
QT_MOC_LITERAL(11, 181, 2), // "ae"
QT_MOC_LITERAL(12, 184, 23), // "comboBoxActionPerformed"
QT_MOC_LITERAL(13, 208, 25), // "adjustTextAreaColumnWidth"
QT_MOC_LITERAL(14, 234, 10), // "scrollPane"
QT_MOC_LITERAL(15, 245, 10), // "JTextArea*"
QT_MOC_LITERAL(16, 256, 8), // "textArea"
QT_MOC_LITERAL(17, 265, 13), // "HtmlTextEdit*"
QT_MOC_LITERAL(18, 279, 4) // "size"

    },
    "Operations::OperationsPanel\0"
    "buttonActionPerformed\0\0QWidget*\0"
    "radioButtonActionPerformed\0"
    "checkBoxActionPerformed\0"
    "addSpinnerChangeListerner\0QSpinBox*\0"
    "s\0spinnerChangeEvent\0ChangeEvent*\0ae\0"
    "comboBoxActionPerformed\0"
    "adjustTextAreaColumnWidth\0scrollPane\0"
    "JTextArea*\0textArea\0HtmlTextEdit*\0"
    "size"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Operations__OperationsPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x09 /* Protected */,
       4,    1,   72,    2, 0x09 /* Protected */,
       5,    1,   75,    2, 0x09 /* Protected */,
       6,    1,   78,    2, 0x09 /* Protected */,
       9,    1,   81,    2, 0x09 /* Protected */,
       9,    0,   84,    2, 0x29 /* Protected | MethodCloned */,
      12,    1,   85,    2, 0x09 /* Protected */,
      13,    2,   88,    2, 0x09 /* Protected */,
      13,    2,   93,    2, 0x09 /* Protected */,
      13,    3,   98,    2, 0x09 /* Protected */,
      13,    3,  105,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,   11,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 15,   14,   16,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 17,   14,   16,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 15, QMetaType::QSize,   14,   16,   18,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 17, QMetaType::QSize,   14,   16,   18,

       0        // eod
};

void Operations::OperationsPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        OperationsPanel *_t = static_cast<OperationsPanel *>(_o);
        switch (_id) {
        case 0: _t->buttonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->radioButtonActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->checkBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->addSpinnerChangeListerner((*reinterpret_cast< QSpinBox*(*)>(_a[1]))); break;
        case 4: _t->spinnerChangeEvent((*reinterpret_cast< ChangeEvent*(*)>(_a[1]))); break;
        case 5: _t->spinnerChangeEvent(); break;
        case 6: _t->comboBoxActionPerformed((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 7: _t->adjustTextAreaColumnWidth((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< JTextArea*(*)>(_a[2]))); break;
        case 8: _t->adjustTextAreaColumnWidth((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< HtmlTextEdit*(*)>(_a[2]))); break;
        case 9: _t->adjustTextAreaColumnWidth((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< JTextArea*(*)>(_a[2])),(*reinterpret_cast< QSize(*)>(_a[3]))); break;
        case 10: _t->adjustTextAreaColumnWidth((*reinterpret_cast< QWidget*(*)>(_a[1])),(*reinterpret_cast< HtmlTextEdit*(*)>(_a[2])),(*reinterpret_cast< QSize(*)>(_a[3]))); break;
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
        case 6:
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
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    }
}

const QMetaObject Operations::OperationsPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Operations__OperationsPanel.data,
      qt_meta_data_Operations__OperationsPanel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Operations::OperationsPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Operations::OperationsPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Operations__OperationsPanel.stringdata))
        return static_cast<void*>(const_cast< OperationsPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int Operations::OperationsPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
