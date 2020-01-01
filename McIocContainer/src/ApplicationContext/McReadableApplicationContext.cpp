#include "include/ApplicationContext/impl/McReadableApplicationContext.h"

#include "include/BeanDefinitionReader/IMcBeanDefinitionReader.h"

struct McReadableApplicationContextData {
    QSharedPointer<IMcBeanDefinitionReader> beanDefinitionReader;
};

McReadableApplicationContext::McReadableApplicationContext(
        IMcConfigurableBeanFactoryConstPtrRef factory
        , IMcBeanDefinitionReaderConstPtrRef reader
        , QObject *parent)
    : McAbstractApplicationContext(factory, parent)
    , d(new McReadableApplicationContextData())
{
    d->beanDefinitionReader = reader;
}

McReadableApplicationContext::~McReadableApplicationContext() {

}
