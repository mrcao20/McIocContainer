#include "HelloWorld.h"

#include "McContainerGlobal.h"

MC_STATIC(HelloWorld)
mcRegisterComponent<HelloWorld, IHelloWorld>("HelloWorld", false);
mcRegisterQVariantListConverter<QSet<int>>();
mcRegisterQVariantMapConverter<QMap<int, QString>>();
MC_STATIC_END

HelloWorld::HelloWorld(QObject *parent) 
	: QObject(parent)
{
}
