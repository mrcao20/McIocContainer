#ifndef _MC_CONTAINER_GLOBAL_H
#define _MC_CONTAINER_GLOBAL_H

#include "McBeanGlobal.h"
#include "McIocContainer.h"

// 需要自动注入的类，则需要调用此函数，否则直接调用mcRegisterBeanFactory
template<typename T>
int mcRegisterComponent(const QString &typeName, const QString &beanName) {
	int typeId = mcRegisterBeanFactory<T>(typeName.toLocal8Bit().data());
	McIocContainer::getInstance()->insertRegistry(typeName, beanName);
	return typeId;
}

// 重载的版本，如果未设置beanName，则默认为将首字母小写的类型名
template<typename T>
int mcRegisterComponent(const QString &typeName) {
	Q_ASSERT(!typeName.isEmpty());
	QChar firstChar = typeName.at(0);
	return mcRegisterComponent<T>(typeName, firstChar.toLower() + typeName.right(typeName.size() - 1));
}

// 需要自动注入的类，则需要调用此函数，否则直接调用mcRegisterBeanFactory
template<typename From, typename To>
int mcRegisterComponent(const QString &typeName, const QString &beanName) {
	int typeId = mcRegisterBeanFactory<From, To>(typeName.toLocal8Bit().data());
	McIocContainer::getInstance()->insertRegistry(typeName, beanName);
	return typeId;
}

// 重载的版本，如果未设置beanName，则默认为将首字母小写的类型名
template<typename From, typename To>
int mcRegisterComponent(const QString &typeName) {
	Q_ASSERT(!typeName.isEmpty());
	QChar firstChar = typeName.at(0);
	return mcRegisterComponent<From, To>(typeName, firstChar.toLower() + typeName.right(typeName.size() - 1));
}

#endif // !_MC_CONTAINER_GLOBAL_H

