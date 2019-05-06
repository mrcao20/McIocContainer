#include "McAbstractBeanFactory.h"

#include <qmap.h>
#include <qdebug.h>
#include <qmutex.h>

#include "IMcBeanDefinition.h"
#include "McBeanReference.h"

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
	QMutexLocker locker(&d->mtx);
	auto beanDefinition = d->map.value(name);
	if (beanDefinition == Q_NULLPTR) {
		qCritical() << "No bean named " << name << " is defined";
		return Q_NULLPTR;
	}
	auto bean = beanDefinition->getBean();
	if (bean == Q_NULLPTR) {	// ���bean������
		bean = doCreate(beanDefinition);	// ����
		if (!bean) {
			qWarning() << QString("failed to create bean '%1'").arg(name);
			return Q_NULLPTR;
		}
		beanDefinition->setBean(bean);		// �Ž�beanDefinition����beanDefinition��������������
	}
	bean->setParent(parent);				// ���ø�����
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
	if (beanRef->getBean()) {	// ���bean�Ѿ���ʵ����������ֱ�ӷ���
		return beanRef->getBean();
	}
	// ����getBean����������bean���õ����ƻ�ȡʵ��
	beanRef->setBean(getBean(beanRef->getName()));
	return beanRef->getBean();
}
