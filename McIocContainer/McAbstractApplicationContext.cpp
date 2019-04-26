#include "McAbstractApplicationContext.h"

struct McAbstractApplicationContextData {
	IMcConfigurableBeanFactory *configurableBeanFactory{ Q_NULLPTR };

	~McAbstractApplicationContextData() {
		MC_SAFE_DELETE(configurableBeanFactory);
	}
};

McAbstractApplicationContext::McAbstractApplicationContext(IMcConfigurableBeanFactory *factory
	, QObject *parent)
	: QObject(parent)
	, d(new McAbstractApplicationContextData())
{
	d->configurableBeanFactory = factory;
}

McAbstractApplicationContext::~McAbstractApplicationContext(){
}

QObject *McAbstractApplicationContext::getBean(const QString &name, QObject *parent) Q_DECL_NOEXCEPT {
	return d->configurableBeanFactory->getBean(name, parent);
}

bool McAbstractApplicationContext::containsBean(const QString &name) Q_DECL_NOEXCEPT {
	return d->configurableBeanFactory->containsBean(name);
}

void McAbstractApplicationContext::registerBeanDefinition(const QString &name
	, IMcBeanDefinition *beanDefinition) Q_DECL_NOEXCEPT {
	d->configurableBeanFactory->registerBeanDefinition(name, beanDefinition);
}
