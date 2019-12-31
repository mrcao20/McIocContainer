#include "include/BeanFactory/impl/McDefaultBeanFactory.h"

#include <qmetaobject.h>
#include <QPluginLoader>
#include <qdebug.h>

#include "include/BeanDefinition/IMcBeanDefinition.h"
#include "include/BeanFactory/impl/McBeanReference.h"
#include "include/PropertyParser/impl/McPropertyParserPlugins.h"
#include "include/PropertyParser/IMcPropertyParser.h"

McDefaultBeanFactory::McDefaultBeanFactory(QObject *parent)
	: McAbstractBeanFactory(parent)
{
}

McDefaultBeanFactory::~McDefaultBeanFactory(){
}

QVariant McDefaultBeanFactory::doCreate(const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT {
    QVariant var;
    QSharedPointer<QObject> bean;
    auto pluginPath = beanDefinition->getPluginPath();
    if(!pluginPath.isEmpty()){
        QPluginLoader loader(pluginPath);
        if (!loader.load()) {
            qWarning() << pluginPath << "cannot load!!";
            return QVariant();
        }
        bean.reset(loader.instance());
    }else{
        auto beanMetaObj = beanDefinition->getBeanMetaObject();
        if (!beanMetaObj) {
            qCritical() << QString("the class '%1' is not in meta-object system").arg(beanDefinition->getClassName());
            return QVariant();
        }
        bean.reset(beanMetaObj->newInstance());
    }
	if (!addPropertyValue(bean, beanDefinition)) {
		qCritical() << QString("failed to init definition '%1'").arg(beanDefinition->getClassName());
        return QVariant();
	}
    var.setValue(bean);
    QString typeName = QString("QSharedPointer<%1>").arg(beanDefinition->getClassName());
    if(!var.convert(QMetaType::type(typeName.toLocal8Bit()))) {
        qCritical() << QString("failed convert QSharedPointer<QObject> to '%1'").arg(typeName);
        return QVariant();
    }
    return var;
}

bool McDefaultBeanFactory::addPropertyValue(const QSharedPointer<QObject>& bean, const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT {
	if (!bean) {
		qCritical() << QString("bean '%1' cannot instantiation, please make sure that have a non-parameter constructor and declared by Q_INVOKABLE")
			.arg(beanDefinition->getClassName());
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
        const auto& parsers = McPropertyParserPlugins::getInstance()->getParsers();
		for (auto parser : parsers) {
			if (parser->convertProperty(bean, metaProperty.typeName(), parsers, this, value))
				break;
		}

        metaProperty.write(bean.data(), value);
	}
	return true;
}
