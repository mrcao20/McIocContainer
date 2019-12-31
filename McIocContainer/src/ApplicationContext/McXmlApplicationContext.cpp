#include "include/ApplicationContext/McXmlApplicationContext.h"

#include "include/BeanFactory/McXmlBeanFactory.h"
#include "include/BeanDefinitionReader/McXmlBeanDefinitionReader.h"

McXmlApplicationContext::McXmlApplicationContext(const QString &location, QObject *parent)
    : McXmlApplicationContext(QSharedPointer<IMcBeanDefinitionReader>(new McXmlBeanDefinitionReader(location)), parent)
{
}

McXmlApplicationContext::McXmlApplicationContext(const QSharedPointer<IMcBeanDefinitionReader>& reader, QObject *parent)
    : McXmlApplicationContext(QSharedPointer<IMcConfigurableBeanFactory>(new McXmlBeanFactory()), reader, parent)
{
}

McXmlApplicationContext::McXmlApplicationContext(const QSharedPointer<IMcConfigurableBeanFactory>& factory, const QSharedPointer<IMcBeanDefinitionReader>& reader, QObject *parent)
	: McDefaultApplicationContext(factory, parent)
{
    reader->readBeanDefinition(factory);
}

McXmlApplicationContext::~McXmlApplicationContext(){
}