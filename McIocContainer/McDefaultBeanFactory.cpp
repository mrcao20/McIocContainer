#include "McDefaultBeanFactory.h"

#include <qmetaobject.h>
#include <qdebug.h>

#include "IMcBeanDefinition.h"
#include "McBeanReference.h"
#include "McPropertyParserPlugins.h"
#include "IMcPropertyParser.h"

McDefaultBeanFactory::McDefaultBeanFactory(QObject *parent)
	: McAbstractBeanFactory(parent)
{
}

McDefaultBeanFactory::~McDefaultBeanFactory(){
}

QObject *McDefaultBeanFactory::doCreate(IMcBeanDefinition *beanDefinition) Q_DECL_NOEXCEPT {
	auto beanMetaObj = beanDefinition->getBeanMetaObject();
	if (!beanMetaObj) {
		qCritical() << QString("the class '%1' is not in meta-object system").arg(beanDefinition->getClassName());
		return Q_NULLPTR;
	}
	auto bean = beanMetaObj->newInstance();
	if (!addPropertyValue(bean, beanDefinition)) {
		qCritical() << QString("failed to init definition '%1'").arg(beanDefinition->getClassName());
		MC_SAFE_DELETE(bean);
		return Q_NULLPTR;
	}
	return bean;
}

bool McDefaultBeanFactory::addPropertyValue(QObject *bean, IMcBeanDefinition *beanDefinition) Q_DECL_NOEXCEPT {
	if (!bean) {
		return false;
	}
	// 循环给定 bean 的属性集合
	auto props = beanDefinition->getProperties();
	for (auto itr = props.cbegin(); itr != props.cend(); ++itr) {
		// 根据给定属性名称获取 给定的bean中的属性对象
		auto metaProperty = bean->metaObject()->property(bean->metaObject()
			->indexOfProperty(itr.key().toLocal8Bit()));
		// 获取定义的属性中的对象
		auto value = itr.value();

		// 解析value
		const QList<IMcPropertyParser *> &parsers = McPropertyParserPlugins::getInstance()->getParsers();
		for (auto parser : parsers) {
			if (parser->convertProperty(bean, metaProperty.typeName(), parsers, this, value))
				break;
		}

		metaProperty.write(bean, value);
	}
	return true;
}
