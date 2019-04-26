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
	// ѭ������ bean �����Լ���
	auto props = beanDefinition->getProperties();
	for (auto itr = props.cbegin(); itr != props.cend(); ++itr) {
		// ���ݸ����������ƻ�ȡ ������bean�е����Զ���
		auto metaProperty = bean->metaObject()->property(bean->metaObject()
			->indexOfProperty(itr.key().toLocal8Bit()));
		// ��ȡ����������еĶ���
		auto value = itr.value();

		// ����value
		const QList<IMcPropertyParser *> &parsers = McPropertyParserPlugins::getInstance()->getParsers();
		for (auto parser : parsers) {
			if (parser->convertProperty(bean, metaProperty.typeName(), parsers, this, value))
				break;
		}

		metaProperty.write(bean, value);
	}
	return true;
}