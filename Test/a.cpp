#include "a.h"

//#include <QPluginLoader>

#include "McIocContainer.h"
#include "McXmlApplicationContext.h"
#include "ReferenceBean.h"
//#include <QMultiHash>
#include "McContainerGlobal.h"

A::A()
{

}

QString A::a(){
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
    McIocContainer::getInstance()->initContainer();
    IMcApplicationContext *appCtx = /*McIocContainer::getInstance()->getApplicationContext();*/new McXmlApplicationContext(":/myspring.xml");
//    ReferenceBean *f = qobject_cast<ReferenceBean *>(appCtx->getBean("referenceBean"));
//    f != nullptr ? f->say() : void();
    QVariant var = appCtx->getBeanToVariant("referenceBean");
    var.value<QSharedPointer<IReferenceBean>>();
    auto f = appCtx->getBeanToVariant("referenceBean").value<QSharedPointer<IReferenceBean>>();
    auto f1 = appCtx->getBeanToVariant("referenceBean").value<QSharedPointer<IReferenceBean>>();
    auto b = appCtx->getBeanToVariant("aaa").value<QSharedPointer<IReferenceBean>>();
    auto b1 = appCtx->getBeanToVariant("aaa").value<QSharedPointer<IReferenceBean>>();
    qDebug() << f << f1 << b << b1;
    f->say();
    f1->say();
    b->say();
    b1->say();
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
