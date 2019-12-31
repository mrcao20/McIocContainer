#include "include/BeanFactory/McAbstractBeanFactory.h"

#include <qmap.h>
#include <qdebug.h>
#include <qmutex.h>

#include "include/BeanDefinition/IMcBeanDefinition.h"
#include "include/BeanFactory/McBeanReference.h"

struct McAbstractBeanFactoryData {
    QMap<QString, QSharedPointer<IMcBeanDefinition>> map;			// 容器
	QMutex mtx{ QMutex::Recursive };				// 递归互斥锁
};

McAbstractBeanFactory::McAbstractBeanFactory(QObject *parent)
	: QObject(parent)
	, d(new McAbstractBeanFactoryData())
{
}

McAbstractBeanFactory::~McAbstractBeanFactory() {
}

QSharedPointer<QObject> McAbstractBeanFactory::getBean(const QString &name) Q_DECL_NOEXCEPT {
    auto var = getBeanToVariant(name);
    if(!var.isValid())
        return QSharedPointer<QObject>();
    return var.value<QSharedPointer<QObject>>();
}

QVariant McAbstractBeanFactory::getBeanToVariant(const QString &name)  Q_DECL_NOEXCEPT {
    QMutexLocker locker(&d->mtx);
    auto beanDefinition = d->map.value(name);
    if (beanDefinition == Q_NULLPTR) {
        qCritical() << "No bean named " << name << " is defined";
        return QVariant();
    }
    auto beanVar = beanDefinition->getBean();
    if (!beanVar.isValid()) {	// 如果bean不存在
        beanVar = doCreate(beanDefinition);	// 创建
        if (!beanVar.isValid()) {
            qWarning() << QString("failed to create bean '%1'").arg(name);
            return QVariant();
        }
        if(beanDefinition->isSingleton())
            beanDefinition->setBean(beanVar);		// 如果为单例时，则放进beanDefinition，以达到复用。
    }
    return beanVar;
}

bool McAbstractBeanFactory::containsBean(const QString &name) Q_DECL_NOEXCEPT {
	return d->map.contains(name);
}

void McAbstractBeanFactory::registerBeanDefinition(const QString &name, const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT {
	d->map.insert(name, beanDefinition);
}

QMap<QString, QSharedPointer<IMcBeanDefinition>> McAbstractBeanFactory::getBeanDefinitions() Q_DECL_NOEXCEPT {
	return d->map;
}

QSharedPointer<QObject> McAbstractBeanFactory::resolveBeanReference(const QSharedPointer<McBeanReference>& beanRef) Q_DECL_NOEXCEPT {
    auto var = resolveBeanReferenceToQVariant(beanRef);
    if(!var.isValid())
        return QSharedPointer<QObject>();
    return var.value<QSharedPointer<QObject>>();
}

QVariant McAbstractBeanFactory::resolveBeanReferenceToQVariant(const QSharedPointer<McBeanReference>& beanRef) Q_DECL_NOEXCEPT {
    if (!beanRef) {
        qCritical() << "beanReference not exists";
        return QVariant();
    }
    // 调用getBeanToVariant方法，根据bean引用的名称获取实例
    return getBeanToVariant(beanRef->getName());
}
