#ifndef _MC_CONTAINER_GLOBAL_H
#define _MC_CONTAINER_GLOBAL_H

#include "McBeanGlobal.h"
#include "McIocContainer.h"

// ��Ҫ�Զ�ע����࣬����Ҫ���ô˺���������ֱ�ӵ���mcRegisterBeanFactory
template<typename T>
int mcRegisterComponent(const QString &typeName, const QString &beanName) {
	int typeId = mcRegisterBeanFactory<T>(typeName.toLocal8Bit().data());
	McIocContainer::getInstance()->insertRegistry(typeName, beanName);
	return typeId;
}

// ���صİ汾�����δ����beanName����Ĭ��Ϊ������ĸСд��������
template<typename T>
int mcRegisterComponent(const QString &typeName) {
	Q_ASSERT(!typeName.isEmpty());
	QChar firstChar = typeName.at(0);
	return mcRegisterComponent<T>(typeName, firstChar.toLower() + typeName.right(typeName.size() - 1));
}

// ��Ҫ�Զ�ע����࣬����Ҫ���ô˺���������ֱ�ӵ���mcRegisterBeanFactory
template<typename From, typename To>
int mcRegisterComponent(const QString &typeName, const QString &beanName) {
	int typeId = mcRegisterBeanFactory<From, To>(typeName.toLocal8Bit().data());
	McIocContainer::getInstance()->insertRegistry(typeName, beanName);
	return typeId;
}

// ���صİ汾�����δ����beanName����Ĭ��Ϊ������ĸСд��������
template<typename From, typename To>
int mcRegisterComponent(const QString &typeName) {
	Q_ASSERT(!typeName.isEmpty());
	QChar firstChar = typeName.at(0);
	return mcRegisterComponent<From, To>(typeName, firstChar.toLower() + typeName.right(typeName.size() - 1));
}

#endif // !_MC_CONTAINER_GLOBAL_H

