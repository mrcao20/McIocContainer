#include "ReferenceBean.h"

#include <QThread>

#include "ApplicationContext/McContainerGlobal.h"
#include "ApplicationContext/impl/McXmlApplicationContext.h"

#define AAA(str) #str
#define TEST_IMPL(Class, ...) AAA(Class##ConstPtrRef)

#define TEST(...) \
    qDebug() << TEST_IMPL(__VA_ARGS__);
    //mcRegisterComponent<__VA_ARGS__>(TEST_IMPL(__VA_ARGS__));

MC_STATIC(ReferenceBean)
//mcRegisterComponent<MC_DECL_TYPELIST(ReferenceBean)>("ReferenceBean");
TEST(MC_DECL_TYPELIST(ReferenceBean))
Mc::Ioc::connect("referenceBean", "this", "signal_bean(QSharedPointer<A>)"
                 , "helloWorld", "slot_hello(QSharedPointer<A>)");
//mcRegisterComponent<ReferenceBean, IReferenceBean>("ReferenceBean");
//mcRegisterComponent<ReferenceBean, IReferenceBean>("ReferenceBean", "aaa", false);
//mcRegisterQVariantListConverter<QList<QVariant>>();
mcRegisterQVariantListConverter<QList<QList<QString>>>();
mcRegisterQVariantListConverter<QList<QSharedPointer<IHelloWorld>>>();
//mcRegisterQVariantListConverter<QList<QSharedPointer<IMcPropertyParserCollection>>>();
mcRegisterQVariantMapConverter<QMap<QString, QSharedPointer<IHelloWorld>>>();
MC_STATIC_END()

#include <QQuickItem>
ReferenceBean::ReferenceBean(QObject *parent)
	: QObject(parent)
{
    qDebug() << "ReferenceBean";
}

ReferenceBean::~ReferenceBean() {
    qDebug() << "~ReferenceBean";
}

void ReferenceBean::aaa(const QString &str, const QSharedPointer<HelloWorld> &h) noexcept {
    qDebug() << str << (void *)h.data() << &h;
    h->say();
}

QJsonObject ReferenceBean::b() noexcept {
    QJsonObject o = {
        {"c", "b"}
    };
    emit signal_bean(QSharedPointer<A>::create());
    return o;
}

QObject *ReferenceBean::o() noexcept {
    auto a = m_hello.dynamicCast<HelloWorld>();
    qDebug() << "-------------" << thread() << a->thread() << QThread::currentThread();
    HelloWorld *h = new HelloWorld();
    h->setText("apaspkf");
    return h;
}

QAbstractItemModel *ReferenceBean::getModel() noexcept {
    qDebug() << m_listModel;
    return m_listModel.data();
}

QMap<QString, QVariant> ReferenceBean::getModels() noexcept {
    QList<QAbstractItemModel*> lists;
    lists << new ListModel() << new ListModel();
//    return QQmlListProperty<QAbstractItemModel>(this, lists);
    QMap<QString, QVariant> varList;
    int i = 0;
    for(auto l : lists) {
        QVariant v;
        v.setValue(l);
        varList.insert(QString::number(i++), v);
    }
    return varList;
}
