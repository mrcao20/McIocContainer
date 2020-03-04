#include "HelloWorld.h"

#include "ApplicationContext/McContainerGlobal.h"

MC_STATIC(HelloWorld)
mcRegisterComponent<MC_DECL_TYPELIST(HelloWorld)>("HelloWorld");
//mcRegisterComponent<HelloWorld, IHelloWorld>("HelloWorld");
mcRegisterQVariantListConverter<QSet<int>>();
mcRegisterQVariantMapConverter<QMap<int, QString>>();
MC_STATIC_END()

HelloWorld::HelloWorld(QObject *parent) 
	: QObject(parent)
{
    qDebug() << "HelloWorld";
}

HelloWorld::~HelloWorld(){
    qDebug() << "~HelloWorld";
}

void HelloWorld::slot_hello(const QSharedPointer<A> &a) {
    qDebug() << a;
}
