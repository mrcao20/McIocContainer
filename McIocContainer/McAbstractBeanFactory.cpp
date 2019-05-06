#include "McAbstractBeanFactory.h"

#include <qmap.h>
#include <qdebug.h>
#include <qmutex.h>

#include "IMcBeanDefinition.h"
#include "McBeanReference.h"

struct McAbstractBeanFactoryData {
	QMap<QString, IMcBeanDefinition *> map;			// 容器
	QMutex mtx{ QMutex::Recursive };				// 递归互斥锁

	~McAbstractBeanFactoryData() {
		// 清除beanDefinition
		qDeleteAll(map);
		map.clear();
	}
};

McAbstractBeanFactory::McAbstractBeanFactory(QObject *parent)
	: QObject(parent)
	, d(new McAbstractBeanFactoryData())
{
}

McAbstractBeanFactory::~McAbstractBeanFactory() {
}

QObject *McAbstractBeanFactory::getBean(const QString &name, QObject *parent) Q_DECL_NOEXCEPT {
	QMutexLocker locker(&d->mtx);
	auto beanDefinition = d->map.value(name);
	if (beanDefinition == Q_NULLPTR) {
		qCritical() << "No bean named " << name << " is defined";
		return Q_NULLPTR;
	}
	auto bean = beanDefinition->getBean();
	if (bean == Q_NULLPTR) {	// 如果bean不存在
		bean = doCreate(beanDefinition);	// 创建
		if (!bean) {
			qWarning() << QString("failed to create bean '%1'").arg(name);
			return Q_NULLPTR;
		}
		beanDefinition->setBean(bean);		// 放进beanDefinition，由beanDefinition管理其生命周期
	}
	bean->setParent(parent);				// 设置父对象
	return bean;
}

bool McAbstractBeanFactory::containsBean(const QString &name) Q_DECL_NOEXCEPT {
	return d->map.contains(name);
}

void McAbstractBeanFactory::registerBeanDefinition(const QString &name, IMcBeanDefinition *beanDefinition) Q_DECL_NOEXCEPT {
	d->map.insert(name, beanDefinition);
}

QMap<QString, IMcBeanDefinition *> McAbstractBeanFactory::getBeanDefinitions() Q_DECL_NOEXCEPT {
	return d->map;
}

QObject *McAbstractBeanFactory::resolveBeanReference(McBeanReference *beanRef) Q_DECL_NOEXCEPT {
	if (!beanRef) {
		qCritical() << "beanReference not exists";
		return Q_NULLPTR;
	}
	if (beanRef->getBean()) {	// 如果bean已经被实例化过，则直接返回
		return beanRef->getBean();
	}
	// 调用getBean方法，根据bean引用的名称获取实例
	beanRef->setBean(getBean(beanRef->getName()));
	return beanRef->getBean();
}
