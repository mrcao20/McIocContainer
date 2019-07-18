/****************************************************************************
** Meta object code from reading C++ file 'ReferenceBean.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Test/ReferenceBean.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ReferenceBean.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ReferenceBean_t {
    QByteArrayData data[7];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ReferenceBean_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ReferenceBean_t qt_meta_stringdata_ReferenceBean = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ReferenceBean"
QT_MOC_LITERAL(1, 14, 0), // ""
QT_MOC_LITERAL(2, 15, 6), // "parent"
QT_MOC_LITERAL(3, 22, 10), // "helloWorld"
QT_MOC_LITERAL(4, 33, 12), // "IHelloWorld*"
QT_MOC_LITERAL(5, 46, 8), // "listData"
QT_MOC_LITERAL(6, 55, 19) // "QList<IHelloWorld*>"

    },
    "ReferenceBean\0\0parent\0helloWorld\0"
    "IHelloWorld*\0listData\0QList<IHelloWorld*>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ReferenceBean[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       2,   18, // properties
       0,    0, // enums/sets
       2,   24, // constructors
       0,       // flags
       0,       // signalCount

 // constructors: parameters
    0x80000000 | 1, QMetaType::QObjectStar,    2,
    0x80000000 | 1,

 // properties: name, type, flags
       3, 0x80000000 | 4, 0x0019500b,
       5, 0x80000000 | 6, 0x0009500b,

 // constructors: name, argc, parameters, tag, flags
       0,    1,   14,    1, 0x0e /* Public */,
       0,    0,   17,    1, 0x2e /* Public | MethodCloned */,

       0        // eod
};

void ReferenceBean::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ReferenceBean *_r = new ReferenceBean((*reinterpret_cast< QObject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 1: { ReferenceBean *_r = new ReferenceBean();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IHelloWorld* >(); break;
        case 1:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<IHelloWorld*> >(); break;
        }
    }

#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        ReferenceBean *_t = static_cast<ReferenceBean *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< IHelloWorld**>(_v) = _t->getHello(); break;
        case 1: *reinterpret_cast< QList<IHelloWorld*>*>(_v) = _t->m_list; break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        ReferenceBean *_t = static_cast<ReferenceBean *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setHello(*reinterpret_cast< IHelloWorld**>(_v)); break;
        case 1:
            if (_t->m_list != *reinterpret_cast< QList<IHelloWorld*>*>(_v)) {
                _t->m_list = *reinterpret_cast< QList<IHelloWorld*>*>(_v);
            }
            break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
}

const QMetaObject ReferenceBean::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ReferenceBean.data,
      qt_meta_data_ReferenceBean,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ReferenceBean::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ReferenceBean::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ReferenceBean.stringdata0))
        return static_cast<void*>(const_cast< ReferenceBean*>(this));
    return QObject::qt_metacast(_clname);
}

int ReferenceBean::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
