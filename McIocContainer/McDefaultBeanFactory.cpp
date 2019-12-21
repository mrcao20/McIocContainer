#include "../include/McDefaultBeanFactory.h"

#include <qmetaobject.h>
#include <QPluginLoader>
#include <qdebug.h>

#include "../include/IMcBeanDefinition.h"
#include "../include/McBeanReference.h"
#include "../include/McPropertyParserPlugins.h"
#include "../include/IMcPropertyParser.h"

McDefaultBeanFactory::McDefaultBeanFactory(QObject *parent)
	: McAbstractBeanFactory(parent)
{
}

McDefaultBeanFactory::~McDefaultBeanFactory(){
}

QVariant McDefaultBeanFactory::doCreate(const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT {
    QVariant var;
    QObject *bean = nullptr;
    auto pluginPath = beanDefinition->getPluginPath();
    if(!pluginPath.isEmpty()){
        QPluginLoader loader(pluginPath);
        if (!loader.load()) {
            qWarning() << pluginPath << "cannot load!!";
            return QVariant();
        }
        bean = loader.instance();
    }else{
        auto beanMetaObj = beanDefinition->getBeanMetaObject();
        if (!beanMetaObj) {
            qCritical() << QString("the class '%1' is not in meta-object system").arg(beanDefinition->getClassName());
            return QVariant();
        }
        bean = beanMetaObj->newInstance();
    }
	if (!addPropertyValue(bean, beanDefinition)) {
		qCritical() << QString("failed to init definition '%1'").arg(beanDefinition->getClassName());
		MC_SAFE_DELETE(bean);
        return QVariant();
	}
    var.setValue(bean);
    if(!var.convert(QMetaType::type(beanDefinition->getClassName().toLocal8Bit()))) {
        qCritical() << QString("failed convert QObject to '%1'").arg(beanDefinition->getClassName());
        MC_SAFE_DELETE(bean);
        return QVariant();
    }
    return var;
}

bool McDefaultBeanFactory::addPropertyValue(QObject *bean, const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT {
	if (!bean) {
		qCritical() << QString("bean '%1' cannot instantiation, please make sure that have a non-parameter constructor and declared by Q_INVOKABLE")
			.arg(beanDefinition->getClassName());
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
