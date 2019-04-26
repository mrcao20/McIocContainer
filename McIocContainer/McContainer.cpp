#include "McContainer.h"

#include <QtCore/qcoreapplication.h>
#include <qmutex.h>
#include <qmetaobject.h>
#include <qdebug.h>

#include "McDefaultApplicationContext.h"
#include "McRootBeanDefinition.h"
#include "McBeanReference.h"
#include "McBeanGlobal.h"

McContainer *McContainer::m_container = Q_NULLPTR;

McContainer::McContainer(QObject *parent)
	: QObject(parent)
{
}

McContainer::~McContainer(){
}

McContainer *McContainer::getInstance() {
	static QMutex mtx;
	if (!m_container) {
		QMutexLocker locker(&mtx);
		if (!m_container) {
			m_container = new McContainer(qApp);
		}
	}
	if (qApp && !m_container->parent()) {
		m_container->setParent(qApp);
	}
	return m_container;
}

void McContainer::initContainer() {
	if (m_applicationContext) {
		qInfo() << "The container has been initialized";
		return;
	}
	mcInitContainer();
	m_applicationContext = new McDefaultApplicationContext(this);
	for (auto itr = m_autowiredRegistry.cbegin(); itr != m_autowiredRegistry.cend(); ++itr) {
		inject(itr.key().toLocal8Bit().data(), itr.value().toLocal8Bit().data());
	}
}

void McContainer::inject(const char *typeName, const char *beanName) {
	IMcBeanDefinition *beanDefinition = new McRootBeanDefinition(this);
	beanDefinition->setClassName(typeName);
	const QMetaObject *metaObj = beanDefinition->getBeanMetaObject();
	Q_ASSERT(metaObj != Q_NULLPTR);
	injectProperty(metaObj, beanDefinition);
	m_applicationContext->registerBeanDefinition(beanName, beanDefinition);
}

void McContainer::injectProperty(const QMetaObject *metaObj, IMcBeanDefinition *beanDefinition) {
	int count = metaObj->propertyCount();
	for (int i = 0; i < count; ++i) {
		QMetaProperty prop = metaObj->property(i);
		if (!prop.isUser()) {
			continue;
		}
		QString typeName = prop.name();
		McBeanReference *beanRef = new McBeanReference(typeName);
		beanDefinition->addProperty(prop.name(), QVariant::fromValue(beanRef));
	}
}
