#pragma once

#include "../BeanFactory/McBeanGlobal.h"
#include "../ApplicationContext/impl/McAnnotationApplicationContext.h"

// 需要自动注入的类，则需要调用此函数，否则直接调用mcRegisterBeanFactory
template<typename T>
int mcRegisterComponent(const QString &typeName, const QString &beanName, bool isSingleton = true) {
	int typeId = mcRegisterBeanFactory<T>(typeName.toLocal8Bit().data());
    McAnnotationApplicationContext::insertRegistry(typeName, beanName, isSingleton);
	return typeId;
}

// 重载的版本，如果未设置beanName，则默认为将首字母小写的类型名
template<typename T>
int mcRegisterComponent(const QString &typeName, bool isSingleton = true) {
	Q_ASSERT(!typeName.isEmpty());
	QChar firstChar = typeName.at(0);
    return mcRegisterComponent<T>(typeName
                                  , firstChar.toLower() + typeName.right(typeName.size() - 1)
                                  , isSingleton);
}

// 需要自动注入的类，则需要调用此函数，否则直接调用mcRegisterBeanFactory
template<typename From, typename To>
int mcRegisterComponent(const QString &typeName, const QString &beanName, bool isSingleton = true) {
	int typeId = mcRegisterBeanFactory<From, To>(typeName.toLocal8Bit().data());
    McAnnotationApplicationContext::insertRegistry(typeName, beanName, isSingleton);
	return typeId;
}

// 重载的版本，如果未设置beanName，则默认为将首字母小写的类型名
template<typename From, typename To>
int mcRegisterComponent(const QString &typeName, bool isSingleton = true) {
	Q_ASSERT(!typeName.isEmpty());
	QChar firstChar = typeName.at(0);
    return mcRegisterComponent<From, To>(typeName
                                         , firstChar.toLower() + typeName.right(typeName.size() - 1)
                                         , isSingleton);
}
