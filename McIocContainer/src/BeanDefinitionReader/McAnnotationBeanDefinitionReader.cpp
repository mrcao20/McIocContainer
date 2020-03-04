#include "include/BeanDefinitionReader/impl/McAnnotationBeanDefinitionReader.h"

#include <qmetaobject.h>

#include "include/BeanFactory/IMcBeanDefinitionRegistry.h"
#include "include/BeanDefinition/IMcBeanDefinition.h"
#include "include/BeanFactory/impl/McBeanReference.h"

struct McAnnotationBeanDefinitionReaderData {
    QHash<QString, QSharedPointer<IMcBeanDefinition>> definitions;
    
    QSharedPointer<IMcBeanDefinitionRegistry> registry;
};

McAnnotationBeanDefinitionReader::McAnnotationBeanDefinitionReader(
        const QHash<QString, QSharedPointer<IMcBeanDefinition>> &definitions
        , QObject *parent)
    : McAbstractBeanDefinitionReader(parent)
    , d(new McAnnotationBeanDefinitionReaderData())
{
    d->definitions = definitions;
}

McAnnotationBeanDefinitionReader::~McAnnotationBeanDefinitionReader() {
}

void McAnnotationBeanDefinitionReader::readBeanDefinition(const QSharedPointer<IMcBeanDefinitionRegistry>& registry) noexcept {
    d->registry = registry;
    QHashIterator<decltype (d->definitions)::key_type, decltype (d->definitions)::mapped_type> iterator(d->definitions);
    while (iterator.hasNext()) {
        auto item = iterator.next();
        auto key = item.key();
        auto value = item.value();
        inject(key, value);
    }
}

void McAnnotationBeanDefinitionReader::inject(
        const QString& beanName
        , const QSharedPointer<IMcBeanDefinition>& beanDefinition) {
    
	const QMetaObject *metaObj = beanDefinition->getBeanMetaObject();
	Q_ASSERT(metaObj != Q_NULLPTR);
	injectProperty(metaObj, beanDefinition);
	d->registry->registerBeanDefinition(beanName, beanDefinition);
}

void McAnnotationBeanDefinitionReader::injectProperty(
        const QMetaObject *metaObj
        , const QSharedPointer<IMcBeanDefinition>& beanDefinition) {
    
	int count = metaObj->propertyCount();
	for (int i = 0; i < count; ++i) {
		QMetaProperty prop = metaObj->property(i);
		if (!prop.isUser()) {
			continue;
		}
		QString typeName = prop.name();
        QSharedPointer<McBeanReference> beanRef = QSharedPointer<McBeanReference>::create();
        beanRef->setName(typeName);
		beanDefinition->addProperty(prop.name(), QVariant::fromValue(beanRef));
	}
}
