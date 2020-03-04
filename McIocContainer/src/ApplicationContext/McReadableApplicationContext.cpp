#include "include/ApplicationContext/impl/McReadableApplicationContext.h"

#include "include/BeanDefinitionReader/IMcBeanDefinitionReader.h"
#include "include/BeanFactory/impl/McDefaultBeanFactory.h"

struct McReadableApplicationContextData {
    QSharedPointer<IMcBeanDefinitionReader> beanDefinitionReader;
    QSharedPointer<IMcBeanDefinitionRegistry> beanDefinitionRegistry;
};

McReadableApplicationContext::McReadableApplicationContext(
        IMcConfigurableBeanFactoryConstPtrRef factory
        , IMcBeanDefinitionReaderConstPtrRef reader
        , QObject *parent)
    : McAbstractApplicationContext(factory, parent)
    , d(new McReadableApplicationContextData())
{
    d->beanDefinitionReader = reader;
    d->beanDefinitionRegistry = factory;
    
    /* 默认不调用此函数，即context默认仍然为懒加载，在IOCBoot中默认调用此函数来达到其
     * 预加载功能，即把是否懒加载的选择权交给用户代码
     */
//    refresh();
    readBeans();
}

McReadableApplicationContext::McReadableApplicationContext(
        IMcBeanDefinitionReaderConstPtrRef reader
        , QObject *parent)
    : McReadableApplicationContext(
          IMcConfigurableBeanFactoryPtr(new McDefaultBeanFactory())
          , reader
          , parent)
{
}

McReadableApplicationContext::~McReadableApplicationContext() {
}

void McReadableApplicationContext::readBeans() noexcept {
    d->beanDefinitionReader->readBeanDefinition(d->beanDefinitionRegistry);
}

void McReadableApplicationContext::doRefresh() noexcept {
    readBeans();
}
