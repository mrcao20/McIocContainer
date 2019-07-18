/****************************************************************************
** Meta object code from reading C++ file 'HelloWorld.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Test/HelloWorld.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QSet>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HelloWorld.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HelloWorld_t {
    QByteArrayData data[12];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HelloWorld_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HelloWorld_t qt_meta_stringdata_HelloWorld = {
    {
QT_MOC_LITERAL(0, 0, 10), // "HelloWorld"
QT_MOC_LITERAL(1, 11, 9), // "Component"
QT_MOC_LITERAL(2, 21, 10), // "Controller"
QT_MOC_LITERAL(3, 32, 3), // "say"
QT_MOC_LITERAL(4, 36, 12), // "MC_AUTOWIRED"
QT_MOC_LITERAL(5, 49, 0), // ""
QT_MOC_LITERAL(6, 50, 6), // "parent"
QT_MOC_LITERAL(7, 57, 4), // "text"
QT_MOC_LITERAL(8, 62, 3), // "map"
QT_MOC_LITERAL(9, 66, 17), // "QMap<int,QString>"
QT_MOC_LITERAL(10, 84, 4), // "list"
QT_MOC_LITERAL(11, 89, 9) // "QSet<int>"

    },
    "HelloWorld\0Component\0Controller\0say\0"
    "MC_AUTOWIRED\0\0parent\0text\0map\0"
    "QMap<int,QString>\0list\0QSet<int>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HelloWorld[] = {

 // content:
       7,       // revision
       0,       // classname
       1,   14, // classinfo
       1,   16, // methods
       3,   26, // properties
       0,    0, // enums/sets
       2,   35, // constructors
       0,       // flags
       0,       // signalCount

 // classinfo: key, value
       1,    2,

 // methods: name, argc, parameters, tag, flags
       3,    0,   21,    4, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void,

 // constructors: parameters
    0x80000000 | 5, QMetaType::QObjectStar,    6,
    0x80000000 | 5,

 // properties: name, type, flags
       7, QMetaType::Bool, 0x00095103,
       8, 0x80000000 | 9, 0x0009510b,
      10, 0x80000000 | 11, 0x0009510b,

 // constructors: name, argc, parameters, tag, flags
       0,    1,   22,    5, 0x0e /* Public */,
       0,    0,   25,    5, 0x2e /* Public | MethodCloned */,

       0        // eod
};

void HelloWorld::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { HelloWorld *_r = new HelloWorld((*reinterpret_cast< QObject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 1: { HelloWorld *_r = new HelloWorld();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        HelloWorld *_t = static_cast<HelloWorld *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->say(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QSet<int> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        HelloWorld *_t = static_cast<HelloWorld *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->getText(); break;
        case 1: *reinterpret_cast< QMap<int,QString>*>(_v) = _t->getMap(); break;
        case 2: *reinterpret_cast< QSet<int>*>(_v) = _t->getList(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        HelloWorld *_t = static_cast<HelloWorld *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setText(*reinterpret_cast< bool*>(_v)); break;
        case 1: _t->setMap(*reinterpret_cast< QMap<int,QString>*>(_v)); break;
        case 2: _t->setList(*reinterpret_cast< QSet<int>*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject HelloWorld::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HelloWorld.data,
      qt_meta_data_HelloWorld,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HelloWorld::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HelloWorld::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HelloWorld.stringdata0))
        return static_cast<void*>(const_cast< HelloWorld*>(this));
    if (!strcmp(_clname, "IHelloWorld"))
        return static_cast< IHelloWorld*>(const_cast< HelloWorld*>(this));
    return QObject::qt_metacast(_clname);
}

int HelloWorld::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
