#include "include/ApplicationContext/impl/McXmlApplicationContext.h"


#include "include/BeanDefinitionReader/impl/McXmlBeanDefinitionReader.h"

McXmlApplicationContext::McXmlApplicationContext(
        const QString &location
        , QObject *parent)
    : McXmlApplicationContext(QStringList() << location, parent)
{
}

McXmlApplicationContext::McXmlApplicationContext(
        const QStringList &locations
        , QObject *parent)
    : McXmlApplicationContext(IMcBeanDefinitionReaderPtr(new McXmlBeanDefinitionReader(locations)), parent)
{
}

McXmlApplicationContext::McXmlApplicationContext(
        IMcBeanDefinitionReaderConstPtrRef reader
        , QObject *parent)
    : McReadableApplicationContext(reader, parent)
{
}

McXmlApplicationContext::McXmlApplicationContext(
        IMcConfigurableBeanFactoryConstPtrRef factory
        , IMcBeanDefinitionReaderConstPtrRef reader
        , QObject *parent)
    : McReadableApplicationContext(factory, reader, parent)
{
}

McXmlApplicationContext::~McXmlApplicationContext(){
}
