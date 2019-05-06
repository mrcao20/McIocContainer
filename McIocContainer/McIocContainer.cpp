#include "McIocContainer.h"

#include <QtCore/qcoreapplication.h>
#include <qmutex.h>
#include <qmetaobject.h>
#include <qdebug.h>

#include "McDefaultApplicationContext.h"
#include "McRootBeanDefinition.h"
#include "McBeanReference.h"
#include "McBeanGlobal.h"

McIocContainer *McIocContainer::m_container = Q_NULLPTR;

McIocContainer::McIocContainer(QObject *parent)
	: QObject(parent)
{
}

McIocContainer::~McIocContainer(){
}

McIocContainer *McIocContainer::getInstance() {
	static QMutex mtx;
	if (!m_container) {
		QMutexLocker locker(&mtx);
		if (!m_container) {
			m_container = new McIocContainer(qApp);
		}
	}
	if (qApp && !m_container->parent()) {
		m_container->setParent(qApp);
	}
	return m_container;
}

void McIocContainer::initContainer() {
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

QList<QString> McIocContainer::getComponent(const QString &componentType) noexcept {
	if (!m_applicationContext) {
		qCritical() << "Please call initContainer to initialize container first";
		return QList<QString>();
	}
	QList<QString> components;
	QMap<QString, IMcBeanDefinition *> beanDefinitions = m_applicationContext->getBeanDefinitions();
	for (auto itr = beanDefinitions.cbegin(); itr != beanDefinitions.cend(); ++itr) {
		auto beanDefinition = itr.value();
		if (!isComponentType(beanDefinition->getBeanMetaObject(), componentType))
			continue;
		components.append(itr.key());
	}
	return components;
}

bool McIocContainer::isComponentType(const QMetaObject *metaObj, const QString &type) noexcept {
	int classInfoCount = metaObj->classInfoCount();
	for (int i = 0; i < classInfoCount; ++i) {
		auto classInfo = metaObj->classInfo(i);
		if (qstrcmp(classInfo.name(), "Component") != 0)
			continue;
		return classInfo.value() == type;
	}
	return false;
}

void McIocContainer::inject(const char *typeName, const char *beanName) {
	IMcBeanDefinition *beanDefinition = new McRootBeanDefinition(this);
	beanDefinition->setClassName(typeName);
	const QMetaObject *metaObj = beanDefinition->getBeanMetaObject();
	Q_ASSERT(metaObj != Q_NULLPTR);
	injectProperty(metaObj, beanDefinition);
	m_applicationContext->registerBeanDefinition(beanName, beanDefinition);
}

void McIocContainer::injectProperty(const QMetaObject *metaObj, IMcBeanDefinition *beanDefinition) {
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
