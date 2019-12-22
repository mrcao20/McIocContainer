#include "../include/McIocContainer.h"

#include <QtCore/qcoreapplication.h>
#include <qmutex.h>
#include <qmetaobject.h>
#include <qdebug.h>

#include "../include/McDefaultApplicationContext.h"
#include "../include/McRootBeanDefinition.h"
#include "../include/McBeanReference.h"
#include "../include/McBeanGlobal.h"

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
    mcRegisterBeanFactory<McBeanReference>();
	m_applicationContext = new McDefaultApplicationContext(this);
	mcInitContainer();
    QHashIterator<decltype (m_autowiredRegistry)::key_type, decltype (m_autowiredRegistry)::mapped_type> iterator(m_autowiredRegistry);
    while (iterator.hasNext()) {
        auto item = iterator.next();
        auto key = item.key();
        auto value = item.value();
        inject(key, value);
    }
}

void McIocContainer::insertRegistry(const QString &typeName, const QString &beanName, bool isSingleton) noexcept {
    auto beanDefinition = m_autowiredRegistry.value(beanName);
    if(beanDefinition) {
        qCritical() << "injected fail. the beanName is exists. it's typeName is" << beanDefinition->getClassName()
                    << ". want inject typeName:" << typeName << "beanName:" << beanName;
        return;
    }
    beanDefinition = QSharedPointer<McRootBeanDefinition>::create();
    beanDefinition->setClassName(typeName);
    beanDefinition->setSingleton(isSingleton);
    m_autowiredRegistry.insert(beanName, beanDefinition);
}

QList<QString> McIocContainer::getComponent(const QString &componentType) noexcept {
	if (!m_applicationContext) {
		qCritical() << "Please call initContainer to initialize container first";
		return QList<QString>();
	}
	QList<QString> components;
    QMap<QString, QSharedPointer<IMcBeanDefinition>> beanDefinitions = m_applicationContext->getBeanDefinitions();
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

void McIocContainer::inject(const QString& beanName, const QSharedPointer<IMcBeanDefinition>& beanDefinition) {
	const QMetaObject *metaObj = beanDefinition->getBeanMetaObject();
	Q_ASSERT(metaObj != Q_NULLPTR);
	injectProperty(metaObj, beanDefinition);
	m_applicationContext->registerBeanDefinition(beanName, beanDefinition);
}

void McIocContainer::injectProperty(const QMetaObject *metaObj, const QSharedPointer<IMcBeanDefinition>& beanDefinition) {
	int count = metaObj->propertyCount();
	for (int i = 0; i < count; ++i) {
		QMetaProperty prop = metaObj->property(i);
		if (!prop.isUser()) {
			continue;
		}
		QString typeName = prop.name();
        QSharedPointer<McBeanReference> beanRef = QSharedPointer<McBeanReference>::create(typeName);
		beanDefinition->addProperty(prop.name(), QVariant::fromValue(beanRef));
	}
}
