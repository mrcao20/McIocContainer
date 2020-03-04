#include "include/ApplicationContext/impl/McAbstractApplicationContext.h"

#include "include/BeanFactory/IMcBeanFactory.h"
#include "include/BeanDefinition/IMcBeanDefinition.h"

struct McAbstractApplicationContextData {
    QSharedPointer<IMcConfigurableBeanFactory> configurableBeanFactory;
};

McAbstractApplicationContext::McAbstractApplicationContext(const QSharedPointer<IMcConfigurableBeanFactory>& factory
        , QObject *parent)
    : QObject(parent)
    , d(new McAbstractApplicationContextData())
{
    d->configurableBeanFactory = factory;
}

McAbstractApplicationContext::~McAbstractApplicationContext(){
}

QSharedPointer<QObject> McAbstractApplicationContext::getBean(const QString &name) Q_DECL_NOEXCEPT {
    return d->configurableBeanFactory->getBean(name);
}

QVariant McAbstractApplicationContext::getBeanToVariant(const QString &name) Q_DECL_NOEXCEPT {
    return d->configurableBeanFactory->getBeanToVariant(name);
}

bool McAbstractApplicationContext::containsBean(const QString &name) Q_DECL_NOEXCEPT {
    return d->configurableBeanFactory->containsBean(name);
}

void McAbstractApplicationContext::registerBeanDefinition(const QString &name, const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT {
    d->configurableBeanFactory->registerBeanDefinition(name, beanDefinition);
}

bool McAbstractApplicationContext::isContained(const QString &name) noexcept {
    return d->configurableBeanFactory->isContained(name);
}

QMap<QString, QSharedPointer<IMcBeanDefinition>> McAbstractApplicationContext::getBeanDefinitions() Q_DECL_NOEXCEPT {
    return d->configurableBeanFactory->getBeanDefinitions();
}

void McAbstractApplicationContext::refresh() noexcept {
    doRefresh();
    
    auto beanDefinitions = getBeanDefinitions();
    auto beanNames = beanDefinitions.keys();    // 获取所有beanName
    for(auto beanName : beanNames) {
        auto beanDefinition = beanDefinitions.value(beanName);
        if(beanDefinition->isSingleton()) {         // 如果不是单例对象则不需要获取，因为非单例对象无法预存
            getBean(beanName);                      // 获取一次bean，让bean预加载
        }
    }
}
