#include "include/BeanFactory/impl/McAbstractBeanFactory.h"

#include <qmap.h>
#include <qdebug.h>
#include <qmutex.h>

#include "include/BeanDefinition/impl/McRootBeanDefinition.h"
#include "include/BeanFactory/impl/McBeanReference.h"

struct McAbstractBeanFactoryData {
    QMap<QString, QSharedPointer<IMcBeanDefinition>> map;			// 容器
	QMutex mtx{ QMutex::Recursive };				// 递归互斥锁
    QThread *targetThread{nullptr};         // 生成对象的目标线程
};

McAbstractBeanFactory::McAbstractBeanFactory(QObject *parent)
	: QObject(parent)
	, d(new McAbstractBeanFactoryData())
{
}

McAbstractBeanFactory::~McAbstractBeanFactory() {
}

QSharedPointer<QObject> McAbstractBeanFactory::getBean(const QString &name, QThread *thread) Q_DECL_NOEXCEPT {
    auto var = getBeanToVariant(name, thread);
    if(!var.isValid())
        return QSharedPointer<QObject>();
    return var.value<QSharedPointer<QObject>>();
}

QVariant McAbstractBeanFactory::getBeanToVariant(const QString &name, QThread *thread)  Q_DECL_NOEXCEPT {
    QMutexLocker locker(&d->mtx);
    d->targetThread = thread;
    auto beanDefinition = d->map.value(name);
    if (beanDefinition == Q_NULLPTR) {
        qCritical() << "No bean named " << name << " is defined";
        return QVariant();
    }
    auto beanVar = beanDefinition->getBean();
    if (!beanVar.isValid()) {	// 如果bean不存在
        beanVar = doCreate(beanDefinition, d->targetThread);	// 创建
        if (!beanVar.isValid()) {
            qWarning() << QString("failed to create bean '%1'").arg(name);
            return QVariant();
        }
        if(beanDefinition->isSingleton())
            beanDefinition->setBean(beanVar);		// 如果为单例时，则放进beanDefinition，以达到复用。
    } else if(thread != nullptr) {
        qWarning() << "the bean of name '" << name << "' is already create."
                   << "specified target thread not be used";
    }
    return beanVar;
}

bool McAbstractBeanFactory::containsBean(const QString &name) Q_DECL_NOEXCEPT {
	return d->map.contains(name);
}

void McAbstractBeanFactory::registerBeanDefinition(const QString &name, const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT {
    // 如果存在则替换
	d->map.insert(name, beanDefinition);
}

bool McAbstractBeanFactory::isContained(const QString &name) noexcept {
    return d->map.contains(name);
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
    auto pluginPath = beanRef->getPluginPath();
    if(!pluginPath.isEmpty()) {
        McRootBeanDefinitionPtr def = McRootBeanDefinitionPtr::create();
        def->setPluginPath(pluginPath);
        auto beanVar = doCreate(def, d->targetThread);
        if (!beanVar.isValid()) {
            qWarning() << QString("failed to create bean of plugin '%1'").arg(pluginPath);
            return QVariant();
        }
        return beanVar;
    }else{
        // 调用getBeanToVariant方法，根据bean引用的名称获取实例
        return getBeanToVariant(beanRef->getName(), d->targetThread);
    }
}
