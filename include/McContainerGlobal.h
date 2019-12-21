#pragma once

#include "McBeanGlobal.h"
#include "McIocContainer.h"

// ��Ҫ�Զ�ע����࣬����Ҫ���ô˺���������ֱ�ӵ���mcRegisterBeanFactory
template<typename T>
int mcRegisterComponent(const QString &typeName, const QString &beanName, bool isSingleton = true) {
	int typeId = mcRegisterBeanFactory<T>(typeName.toLocal8Bit().data());
    McIocContainer::getInstance()->insertRegistry(typeName, beanName, isSingleton);
	return typeId;
}

// ���صİ汾�����δ����beanName����Ĭ��Ϊ������ĸСд��������
template<typename T>
int mcRegisterComponent(const QString &typeName, bool isSingleton = true) {
	Q_ASSERT(!typeName.isEmpty());
	QChar firstChar = typeName.at(0);
    return mcRegisterComponent<T>(typeName
                                  , firstChar.toLower() + typeName.right(typeName.size() - 1)
                                  , isSingleton);
}

// ��Ҫ�Զ�ע����࣬����Ҫ���ô˺���������ֱ�ӵ���mcRegisterBeanFactory
template<typename From, typename To>
int mcRegisterComponent(const QString &typeName, const QString &beanName, bool isSingleton = true) {
	int typeId = mcRegisterBeanFactory<From, To>(typeName.toLocal8Bit().data());
    McIocContainer::getInstance()->insertRegistry(typeName, beanName, isSingleton);
	return typeId;
}

// ���صİ汾�����δ����beanName����Ĭ��Ϊ������ĸСд��������
template<typename From, typename To>
int mcRegisterComponent(const QString &typeName, bool isSingleton = true) {
	Q_ASSERT(!typeName.isEmpty());
	QChar firstChar = typeName.at(0);
    return mcRegisterComponent<From, To>(typeName
                                         , firstChar.toLower() + typeName.right(typeName.size() - 1)
                                         , isSingleton);
}
