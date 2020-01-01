#include "include/ApplicationContext/impl/McXmlApplicationContext.h"

#include "include/BeanFactory/impl/McDefaultBeanFactory.h"
#include "include/BeanDefinitionReader/impl/McXmlBeanDefinitionReader.h"

McXmlApplicationContext::McXmlApplicationContext(const QString &location, QObject *parent)
    : McXmlApplicationContext(IMcBeanDefinitionReaderPtr(new McXmlBeanDefinitionReader(location)), parent)
{
}

McXmlApplicationContext::McXmlApplicationContext(IMcBeanDefinitionReaderConstPtrRef reader, QObject *parent)
    : McXmlApplicationContext(IMcConfigurableBeanFactoryPtr(new McDefaultBeanFactory()), reader, parent)
{
}

McXmlApplicationContext::McXmlApplicationContext(IMcConfigurableBeanFactoryConstPtrRef factory, IMcBeanDefinitionReaderConstPtrRef reader, QObject *parent)
    : McReadableApplicationContext(factory, reader, parent)
{
}

McXmlApplicationContext::~McXmlApplicationContext(){
}
