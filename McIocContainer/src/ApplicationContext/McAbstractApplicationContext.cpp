#include "include/ApplicationContext/McAbstractApplicationContext.h"

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

void McAbstractApplicationContext::registerBeanDefinition(const QString &name
    , const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT {
	d->configurableBeanFactory->registerBeanDefinition(name, beanDefinition);
}

QMap<QString, QSharedPointer<IMcBeanDefinition>> McAbstractApplicationContext::getBeanDefinitions() Q_DECL_NOEXCEPT {
	return d->configurableBeanFactory->getBeanDefinitions();
}
