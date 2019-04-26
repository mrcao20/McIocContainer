/*******************************************************************
 <文件名>		McContainer.h
 <详细说明>		全局唯一的容器，用于自动注入。
				程序开始时必须调用initContainer函数初始化容器，否则自动注入将不会成功。
				由于C++静态变量初始化顺序不确定，所以此处的单例模式使用双重加锁。
 <作   者>		mrcao
 <日   期>		2019/4/7
********************************************************************/

#ifndef _MC_CONTAINER_H_
#define _MC_CONTAINER_H_

#include <QObject>
#include "McMacroGlobal.h"

#include <qmap.h>

class IMcApplicationContext;
class IMcBeanDefinition;

class MCIOCCONTAINER_EXPORT McContainer : public QObject {
	Q_OBJECT

public:
	~McContainer();

	static McContainer *getInstance();

	void initContainer();

	void insertRegistry(const QString &typeName, const QString &beanName) {
		m_autowiredRegistry.insert(typeName, beanName);
	}

	IMcApplicationContext *getApplicationContext() {
		return m_applicationContext;
	}

private:
	void inject(const char *typeName, const char *beanName);
	void injectProperty(const QMetaObject *metaObj, IMcBeanDefinition *beanDefinition);

private:
	static McContainer *m_container;

	IMcApplicationContext *m_applicationContext{ Q_NULLPTR };
	QMap<QString, QString> m_autowiredRegistry;	// 用来保存需要自动注入的bean的typeName和beanName

private:
	explicit McContainer(QObject *parent = 0);
};

#endif // !_MC_CONTAINER_H_