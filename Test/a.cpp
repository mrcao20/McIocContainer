#include "a.h"

//#include <QPluginLoader>

#include "McIocBoot.h"
#include "ApplicationContext/impl/McXmlApplicationContext.h"
#include "ReferenceBean.h"
//#include <QMultiHash>
#include "ApplicationContext/McContainerGlobal.h"
#include <QMutexLocker>
#include <QQmlEngine>
#include <QJSEngine>
#include "HelloWorld.h"

MC_STATIC(A)
mcRegisterComponent<A>("A");
MC_STATIC_END()

A::A()
{
    qDebug() << "A";
}

A::~A(){
    qDebug() << "~A";
}

QObject *A::a(){
    HelloWorld *h = new HelloWorld();
    AAA *aaa = new AAA();
    aaa->h = h;
    return h;
}

QJsonObject A::b(const QJsonObject &o) {
    qDebug() << o["c"];
    qDebug() << o;
    return QJsonObject({{"a", "b"}});
}

void A::c(QJSValue func) {
    func.call();
}

QVariant A::bbb() {
    QSharedPointer<ReferenceBean> r = QSharedPointer<ReferenceBean>::create();
    QVariant v;
    v.setValue(r);
    return v;
}

void A::slot_a() {
    qDebug() << "slot_a";
}
