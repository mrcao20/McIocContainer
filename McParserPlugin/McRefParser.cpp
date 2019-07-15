#include "McRefParser.h"

#include <qdom.h>
#include <qdebug.h>
#include <qmetaobject.h>

#include "IMcBeanDefinition.h"
#include "McBeanReference.h"
#include "IMcBeanReferenceResolver.h"

McRefParser::McRefParser(QObject *parent)
	: QObject(parent)
{
}

McRefParser::~McRefParser(){
}

bool McRefParser::parseProperty(const QDomElement &propEle, const QList<IMcPropertyParser *> &parsers, QVariant &value) const noexcept {
    Q_UNUSED(parsers);
    QDomElement childEle = propEle.firstChildElement("ref");
    if (propEle.elementsByTagName("ref").size() > 1 || (!propEle.hasAttribute("ref") && propEle.tagName() != "ref" && childEle.isNull()))
		return false;		// 不存在ref，本对象不解析

	// 存在ref，开始解析
	QString ref = "";
	if (propEle.hasAttribute("ref"))
		ref = propEle.attribute("ref");
	else {
		if (propEle.tagName() == "ref")
			childEle = propEle;
		if (childEle.hasAttribute("bean"))
			ref = childEle.attribute("bean");
		else
			ref = childEle.text();
	}

	if (!ref.isEmpty()) {
		// 如果不为空，则创建一个 “bean的引用” 实例，构造参数为名称，实例暂时为空
		McBeanReference *beanRef = new McBeanReference(ref);
		value = QVariant::fromValue(beanRef);
	}
	return true;
}

bool McRefParser::convertProperty(QObject *bean, const char *propTypeName, const QList<IMcPropertyParser *> &parsers, IMcBeanReferenceResolver *refResolver, QVariant &value) const noexcept {
    Q_UNUSED(parsers);
    // 判断属性值是否是一个beanReference
	if (!value.canConvert<QObject *>())
		return false;	// 本解析器无法解析，传递给其他解析器解析
	// 如果是就将其转换
	auto obj = value.value<QObject *>();
	if (!obj->inherits("McBeanReference")) {	// 第二步判断这个对象是否是 BeanReference 对象
		// 失败，记录错误信息
		qCritical() << "cannot inject beanReference";
		return true;
	}
	// 将属性对象转为BeanReference对象，因为上一步判断了obj是否实现至McBeanReference，故此处一定成功
	auto beanReference = qobject_cast<McBeanReference *>(obj);
	// 调用父类的AbstractBeanFactory的resolveBeanReference方法，根据bean获取实例，此处即是递归
	obj = refResolver->resolveBeanReference(beanReference);
	if (!obj) {
		// 失败，记录错误信息
		qCritical() << "cannot get bean from beanReference";
		return true;
	}
	// 反射注入bean的属性，新得到的bean是当前bean的子对象，所以设置新bean的父对象为当前bean
	obj->setParent(bean);
	value = QVariant::fromValue(obj);
	QString oldTypeName = value.typeName();
	// 先将value转换为具体实现类
	if (!value.convert(QMetaType::type(obj->metaObject()->className()))) {
		qCritical() << QString("无法将%1转换为%2，请保证他们为继承关系或使用mcRegisterBeanFactory<%3, %4>()注册过").arg(
			oldTypeName, propTypeName, oldTypeName, propTypeName);
		return true;
	}
	oldTypeName = value.typeName();
	if (qstrcmp(value.typeName(), propTypeName) == 0)
		return true;
//#if !defined(Q_NO_TEMPLATE_FRIENDS) && !defined(Q_CC_MSVC)
//	value = QVariant(value.userType(), value.constData());
//#else
//	value.d.is_null = false;
//#endif
	value.data_ptr().is_null = false;
	// 再将实现类转换为类中所需要的接口
	if (!value.convert(QMetaType::type(propTypeName)))
		qCritical() << QString("无法将%1转换为%2，请保证他们为继承关系或使用mcRegisterBeanFactory<%3, %4>()注册过").arg(
			oldTypeName, propTypeName, oldTypeName, propTypeName);
	return true;
}
