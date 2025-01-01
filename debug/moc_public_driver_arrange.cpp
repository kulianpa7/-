/****************************************************************************
** Meta object code from reading C++ file 'public_driver_arrange.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../public_driver_arrange.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'public_driver_arrange.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSpublic_driver_arrangeENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSpublic_driver_arrangeENDCLASS = QtMocHelpers::stringData(
    "public_driver_arrange",
    "onDateChanged",
    "",
    "date",
    "combo_driver",
    "combo_car",
    "on_driver_changed",
    "combo_box_car",
    "push_button_checkboxANDcombobox",
    "QList<QList<int>>",
    "vec",
    "weekday",
    "save",
    "deleteAllForMonth",
    "clear_check"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSpublic_driver_arrangeENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x08,    1 /* Private */,
       4,    0,   71,    2, 0x08,    3 /* Private */,
       5,    0,   72,    2, 0x08,    4 /* Private */,
       6,    0,   73,    2, 0x08,    5 /* Private */,
       7,    0,   74,    2, 0x08,    6 /* Private */,
       8,    2,   75,    2, 0x08,    7 /* Private */,
      12,    0,   80,    2, 0x08,   10 /* Private */,
      13,    0,   81,    2, 0x08,   11 /* Private */,
      14,    0,   82,    2, 0x08,   12 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QDate,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,   10,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject public_driver_arrange::staticMetaObject = { {
    QMetaObject::SuperData::link<BasePage::staticMetaObject>(),
    qt_meta_stringdata_CLASSpublic_driver_arrangeENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSpublic_driver_arrangeENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSpublic_driver_arrangeENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<public_driver_arrange, std::true_type>,
        // method 'onDateChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QDate &, std::false_type>,
        // method 'combo_driver'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'combo_car'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_driver_changed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'combo_box_car'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'push_button_checkboxANDcombobox'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QVector<QVector<int>>, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'save'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteAllForMonth'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clear_check'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void public_driver_arrange::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<public_driver_arrange *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onDateChanged((*reinterpret_cast< std::add_pointer_t<QDate>>(_a[1]))); break;
        case 1: _t->combo_driver(); break;
        case 2: _t->combo_car(); break;
        case 3: _t->on_driver_changed(); break;
        case 4: _t->combo_box_car(); break;
        case 5: _t->push_button_checkboxANDcombobox((*reinterpret_cast< std::add_pointer_t<QList<QList<int>>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->save(); break;
        case 7: _t->deleteAllForMonth(); break;
        case 8: _t->clear_check(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QList<int>> >(); break;
            }
            break;
        }
    }
}

const QMetaObject *public_driver_arrange::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *public_driver_arrange::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSpublic_driver_arrangeENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return BasePage::qt_metacast(_clname);
}

int public_driver_arrange::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BasePage::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
