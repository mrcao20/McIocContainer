/*******************************************************************
 <�ļ���>		McContainer.h
 <��ϸ˵��>		ȫ��Ψһ�������������Զ�ע�롣
				����ʼʱ�������initContainer������ʼ�������������Զ�ע�뽫����ɹ���
				����C++��̬������ʼ��˳��ȷ�������Դ˴��ĵ���ģʽʹ��˫�ؼ�����
 <��   ��>		mrcao
 <��   ��>		2019/4/7
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
	QMap<QString, QString> m_autowiredRegistry;	// ����������Ҫ�Զ�ע���bean��typeName��beanName

private:
	explicit McContainer(QObject *parent = 0);
};

#endif // !_MC_CONTAINER_H_