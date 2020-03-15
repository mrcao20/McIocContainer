#include "include/BeanFactory/impl/McDefaultBeanFactory.h"

#include <qmetaobject.h>
#include <QPluginLoader>
#include <qdebug.h>

#include "include/BeanDefinition/IMcBeanDefinition.h"
#include "include/BeanFactory/impl/McBeanReference.h"
#include "include/BeanFactory/impl/McBeanConnector.h"
#include "include/PropertyParser/impl/McPropertyParserPlugins.h"
#include "include/PropertyParser/IMcPropertyParser.h"

McDefaultBeanFactory::McDefaultBeanFactory(QObject *parent)
	: McAbstractBeanFactory(parent)
{
}

McDefaultBeanFactory::~McDefaultBeanFactory(){
}

QVariant McDefaultBeanFactory::doCreate(const QSharedPointer<IMcBeanDefinition>& beanDefinition, QThread *thread) Q_DECL_NOEXCEPT {
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
    if (!bean) {
		qCritical() << QString("bean '%1' cannot instantiation, please make sure that have a non-parameter constructor and declared by Q_INVOKABLE")
			.arg(beanDefinition->getClassName());
		return QVariant();
	}
    QVariantMap proValues;
	if (!addPropertyValue(bean, beanDefinition, proValues)) {
		qCritical() << QString("failed to init definition '%1'").arg(bean->metaObject()->className());
        return QVariant();
	}
    if(!addObjectConnect(bean, beanDefinition, proValues)) {
        qCritical() << QString("failed to add object connect '%1'").arg(bean->metaObject()->className());
        return QVariant();
    }
    if(thread != nullptr && thread != bean->thread()) {
        bean->moveToThread(thread);
    }
    var.setValue(bean);
    QString typeName = QString("QSharedPointer<%1>").arg(bean->metaObject()->className());
    if(!var.convert(QMetaType::type(typeName.toLocal8Bit()))) {
        qCritical() << QString("failed convert QSharedPointer<QObject> to '%1'").arg(typeName);
        return QVariant();
    }
    return var;
}

bool McDefaultBeanFactory::addPropertyValue(
        const QSharedPointer<QObject> &bean
        , const QSharedPointer<IMcBeanDefinition> &beanDefinition
        , QVariantMap &proValues) Q_DECL_NOEXCEPT {
    
	// 循环给定 bean 的属性集合
	auto props = beanDefinition->getProperties();
	for (auto itr = props.cbegin(); itr != props.cend(); ++itr) {
		// 根据给定属性名称获取 给定的bean中的属性对象
        auto index = bean->metaObject()->indexOfProperty(itr.key().toLocal8Bit());
        if(index == -1) {
            qCritical() << QString("bean '%1' 没有找到属性名为 '%2' 的属性")
                           .arg(bean->metaObject()->className(), itr.key());
            return false;
        }
		auto metaProperty = bean->metaObject()->property(index);
		// 获取定义的属性中的对象
		auto value = itr.value();
        
		// 解析value
        const auto& parsers = McPropertyParserPlugins::getInstance()->getParsers();
		for (auto parser : parsers) {
			if (parser->convertProperty(bean, metaProperty.typeName(), parsers, this, value))
				break;
		}
        
        proValues.insert(itr.key(), value);
        metaProperty.write(bean.data(), value);
	}
	return true;
}

bool McDefaultBeanFactory::addObjectConnect(
        const QSharedPointer<QObject> &bean
        , const QSharedPointer<IMcBeanDefinition> &beanDefinition
        , const QVariantMap &proValues) Q_DECL_NOEXCEPT {
    
    auto connectors = beanDefinition->getConnectors();
    for(auto connector : connectors) {
        McBeanConnectorPtr con = connector.value<McBeanConnectorPtr>();
        if(!con) {
            qCritical() << QString("bean '%1' 存在一个connector，但不能转换为QSharedPointer<McBeanConnector>")
                           .arg(bean->metaObject()->className());
            return false;
        }
        QObject *sender = nullptr;
        QMetaMethod signal;
        QObject *receiver = nullptr;
        QMetaMethod slot;
        Qt::ConnectionType type;
        
        QString senderProName = con->getSender();
        sender = getPropertyObject(bean, senderProName, proValues);
        if(sender == nullptr) {
            return false;
        }
        auto signalMetaObj = sender->metaObject();
        
        QString signalStr = con->getSignal();
        if(signalStr.isEmpty()) {
            qCritical() << "信号名不能为空";
            return false;
        }
        int signalIndex = signalMetaObj->indexOfSignal(signalStr.toLocal8Bit());
        if(signalIndex == -1) {
            qCritical() << QString("bean '%1' 不存在名为 '%2' 的信号").arg(signalMetaObj->className(), signalStr);
            return false;
        }
        signal = signalMetaObj->method(signalIndex);
        
        QString receiverProName = con->getReceiver();
        receiver = getPropertyObject(bean, receiverProName, proValues);
        if(receiver == nullptr) {
            return false;
        }
        auto slotMetaObj = receiver->metaObject();
        
        QString slotStr = con->getSlot();
        if(slotStr.isEmpty()) {
            qCritical() << "槽名不能为空";
            return false;
        }
        int slotIndex = slotMetaObj->indexOfMethod(slotStr.toLocal8Bit());
        if(slotIndex == -1) {
            qCritical() << QString("bean '%1' 不存在名为 '%2' 的槽").arg(slotMetaObj->className(), slotStr);
            return false;
        }
        slot = slotMetaObj->method(slotIndex);
        
        type = con->getType();
        
        QObject::connect(sender, signal, receiver, slot, type);
    }
    return true;
}

QObject *McDefaultBeanFactory::getPropertyObject(
        const QSharedPointer<QObject> &bean
        , const QString &proName
        , const QVariantMap &proValues) Q_DECL_NOEXCEPT {
    
    QObject *obj = nullptr;
    if(proName == MC_THIS) {
        obj = bean.data();
    }else{
        if(!proValues.contains(proName)) {
            qCritical() << QString("bean '%1' 没有找到属性名为 '%2' 的属性")
                           .arg(bean->metaObject()->className(), proName);
            return nullptr;
        }
        auto varPro = proValues[proName];
        obj = varPro.value<QSharedPointer<QObject>>().data();
    }
    return obj;
}
