#include "HelloWorld.h"

#include "McContainerGlobal.h"

MC_STATIC(HelloWorld)
mcRegisterBeanFactory<HelloWorld, IHelloWorld>("HelloWorld");
//mcRegisterComponent<HelloWorld, IHelloWorld>("HelloWorld");
mcRegisterQVariantListConverter<QSet<int>>();
mcRegisterQVariantMapConverter<QMap<int, QString>>();
MC_STATIC_END

HelloWorld::HelloWorld(QObject *parent) 
	: QObject(parent)
{
}
