#include "../include/McAbstractBeanFactory.h"

#include <qmap.h>
#include <qdebug.h>
#include <qmutex.h>

#include "../include/IMcBeanDefinition.h"
#include "../include/McBeanReference.h"

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
    auto var = getBeanToVariant(name, parent);
    if(!var.isValid())
        return nullptr;
    return var.value<QObject*>();
}

QVariant McAbstractBeanFactory::getBeanToVariant(const QString &name, QObject *parent)  Q_DECL_NOEXCEPT {
    QMutexLocker locker(&d->mtx);
    auto beanDefinition = d->map.value(name);
    if (beanDefinition == Q_NULLPTR) {
        qCritical() << "No bean named " << name << " is defined";
        return QVariant();
    }
    auto beanVar = beanDefinition->getBean();
    QObject* bean = nullptr;
    if (!beanVar.isValid()) {	// 如果bean不存在
        beanVar = doCreate(beanDefinition);	// 创建
        if (!beanVar.isValid()) {
            qWarning() << QString("failed to create bean '%1'").arg(name);
            return QVariant();
        }
        beanDefinition->setBean(beanVar);		// 放进beanDefinition，以达到复用，后续单利时不需要设置进去
    }
    bean = beanVar.value<QObject*>();
    bean->setParent(parent);				// 设置父对象
    return beanVar;
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
