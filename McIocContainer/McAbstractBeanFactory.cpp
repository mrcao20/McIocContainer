#include "../include/McAbstractBeanFactory.h"

#include <qmap.h>
#include <qdebug.h>
#include <qmutex.h>

#include "../include/IMcBeanDefinition.h"
#include "../include/McBeanReference.h"

struct McAbstractBeanFactoryData {
	QMap<QString, IMcBeanDefinition *> map;			// ����
	QMutex mtx{ QMutex::Recursive };				// �ݹ黥����

	~McAbstractBeanFactoryData() {
		// ���beanDefinition
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
    if (!beanVar.isValid()) {	// ���bean������
        beanVar = doCreate(beanDefinition);	// ����
        if (!beanVar.isValid()) {
            qWarning() << QString("failed to create bean '%1'").arg(name);
            return QVariant();
        }
        beanDefinition->setBean(beanVar);		// �Ž�beanDefinition���Դﵽ���ã���������ʱ����Ҫ���ý�ȥ
    }
    bean = beanVar.value<QObject*>();
    bean->setParent(parent);				// ���ø�����
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
	if (beanRef->getBean()) {	// ���bean�Ѿ���ʵ����������ֱ�ӷ���
		return beanRef->getBean();
	}
	// ����getBean����������bean���õ����ƻ�ȡʵ��
	beanRef->setBean(getBean(beanRef->getName()));
	return beanRef->getBean();
}
