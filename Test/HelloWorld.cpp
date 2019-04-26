#include "HelloWorld.h"

#include "McContainerGlobal.h"

MC_STATIC(HelloWorld)
mcRegisterComponent<HelloWorld *, IHelloWorld *>("HelloWorld");
mcRegisterListConverter<QSet<int>>();
mcRegisterMapConverter<QMap<int, QString>>();
MC_STATIC_END

HelloWorld::HelloWorld(QObject *parent) 
	: QObject(parent)
{
}