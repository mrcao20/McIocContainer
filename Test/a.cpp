#include "a.h"

//#include <QPluginLoader>

#include "McIocContainer.h"
#include "ApplicationContext/impl/McXmlApplicationContext.h"
#include "ReferenceBean.h"
//#include <QMultiHash>
#include "ApplicationContext/McContainerGlobal.h"
#include <QMutexLocker>

A::A()
{

}

namespace McPrivate {

template <typename...> struct TypeList;

template <typename T, typename... U>
struct TypeList<T, U...> {
    using Head = T;
    using Tails = TypeList<U...>;
};

// 针对空list的特化
template <>
struct TypeList<> {};

}

class P {
public:
    virtual ~P() = default;
    using TypeList = McPrivate::TypeList<>;
};

class I {
public:
    virtual ~I() = default;
    using TypeList = McPrivate::TypeList<>;
};

class O : public QObject, public I {
    Q_OBJECT
public:
    using TypeList = McPrivate::TypeList<QObject, I, I::TypeList>;
};

class D : public O, public P {
public:
    using TypeList = McPrivate::TypeList<O::TypeList, P, O, P::TypeList>;
};

template<typename From, typename To>
struct Converter {
    static void converter(){
        qDebug() << "mmmmmmmmmmm";
    }
};

template<typename T, typename... U>
struct Converter<T, McPrivate::TypeList<U...>> {
    static void converter(){
        qDebug() << "aaaaaaaa";
        using TypeList = McPrivate::TypeList<U...>;
        Converter<T, typename TypeList::Head>::converter();
        Converter<T, typename TypeList::Tails>::converter();
    }
};

template<typename From>
struct Converter<From, QObject> {
    static void converter(){
        qDebug() << "llllllllll";
    }
};

template<typename T>
struct Converter<T, McPrivate::TypeList<>> {
    static void converter(){
        qDebug() << "bbbbbbbbbb";
    }
};

QString A::a(){
    //Converter<D, D::TypeList>::converter();
//    QMultiHash<QString, QString> hash;
//    hash.insert("a", "fff");
//    hash.insert("a", "eeee");
//    hash.insert("b", "fff");
//    QHashIterator<QString, QString> i(hash);
//    qDebug() << hash.keys("fff");
//    while (i.hasNext()) {
//        auto item = i.next();
//        qDebug() << item.key() << item.value();
//    }
    QSharedPointer<ReferenceBean> r;
    r.reset(new ReferenceBean());
    qDebug() << r->sharedFromThis();
    McIocContainer::getInstance()->initContainer();
    IMcApplicationContext *appCtx = /*McIocContainer::getInstance()->getApplicationContext();*/new McXmlApplicationContext(":/myspring.xml");
//    ReferenceBean *f = qobject_cast<ReferenceBean *>(appCtx->getBean("referenceBean"));
//    f != nullptr ? f->say() : void();
//    QVariant var = appCtx->getBeanToVariant("referenceBean");
//    var.value<QSharedPointer<IReferenceBean>>();
//    auto f = appCtx->getBeanToVariant("referenceBean").value<QSharedPointer<IRR>>();
//    auto f1 = appCtx->getBeanToVariant("referenceBean").value<QSharedPointer<IReferenceBean>>();
//    auto b = appCtx->getBeanToVariant("aaa").value<QSharedPointer<IReferenceBean>>();
//    auto b1 = appCtx->getBeanToVariant("aaa").value<QSharedPointer<IReferenceBean>>();
//    qDebug() << f << f1 << b << b1;
//    f->say();
//    f1->say();
//    b->say();
//    b1->say();
//    QSharedPointer<ReferenceBean> r = QSharedPointer<ReferenceBean>::create();
//    auto metaobj = r->metaObject();
//    qDebug() << metaobj->className();
//    QString x = "QSharedPointer<";
//    x += metaobj->className();
//    x += ">";
//    qDebug() << x;
//    qDebug() << QMetaType::type(x.toLocal8Bit().data());
//    QVariant v;
//    v.setValue(r);
//    qDebug() << v.userType();
//    qDebug() << v.canConvert<QSharedPointer<QObject>>();
//    qDebug() << v.canConvert<QSharedPointer<IReferenceBean>>();
//    QSharedPointer<QObject> o = v.value<QSharedPointer<QObject>>();
//    QSharedPointer<IReferenceBean> i = v.value<QSharedPointer<IReferenceBean>>();
//    qDebug() << o << i;
//    auto xxx = bbb();
//    auto zzzz = xxx.value<QSharedPointer<ReferenceBean>>();
//    zzzz->say();
    return "aaa";
}

QVariant A::bbb() {
    QSharedPointer<ReferenceBean> r = QSharedPointer<ReferenceBean>::create();
    QVariant v;
    v.setValue(r);
    return v;
}
