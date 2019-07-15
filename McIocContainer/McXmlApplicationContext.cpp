#include "../include/McXmlApplicationContext.h"

#include "../include/McXmlBeanFactory.h"
#include "../include/McXmlBeanDefinitionReader.h"

McXmlApplicationContext::McXmlApplicationContext(const QString &location, QObject *parent)
	: McXmlApplicationContext(new McXmlBeanDefinitionReader(location), parent)
{
}

McXmlApplicationContext::McXmlApplicationContext(IMcBeanDefinitionReader *reader, QObject *parent)
	: McXmlApplicationContext(new McXmlBeanFactory(reader), parent)
{
}

McXmlApplicationContext::McXmlApplicationContext(McXmlBeanFactory *factory, QObject *parent)
	: McDefaultApplicationContext(factory, parent)
{
}

McXmlApplicationContext::~McXmlApplicationContext(){
}
