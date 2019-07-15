/*******************************************************************
 <�ļ���>		McIocContainer.h
 <��ϸ˵��>		ȫ��Ψһ�������������Զ�ע�롣
				����ʼʱ�������initContainer������ʼ�������������Զ�ע�뽫����ɹ���
				����C++��̬������ʼ��˳��ȷ�������Դ˴��ĵ���ģʽʹ��˫�ؼ�����
 <��   ��>		mrcao
 <��   ��>		2019/4/7
********************************************************************/

#ifndef _MC_IOC_CONTAINER_H_
#define _MC_IOC_CONTAINER_H_

#include <QObject>
#include "McMacroGlobal.h"

#include <qmap.h>

class IMcApplicationContext;
class IMcBeanDefinition;

class MCIOCCONTAINER_EXPORT McIocContainer : public QObject {
	Q_OBJECT

public:
	~McIocContainer();

	static McIocContainer *getInstance();

	// ��ʼ���������˺������̰߳�ȫ�������ظ���ʼ��
	void initContainer();

	void insertRegistry(const QString &typeName, const QString &beanName) {
		m_autowiredRegistry.insert(typeName, beanName);
	}

	// ��ȡ�����齨����ΪcomponentType��bean������
	QList<QString> getComponent(const QString &componentType) noexcept;
	// �����Ԫ�������������Ƿ�Ϊtype
	bool isComponentType(const QMetaObject *metaObj, const QString &type) noexcept;

	IMcApplicationContext *getApplicationContext() {
		return m_applicationContext;
	}

private:
	void inject(const char *typeName, const char *beanName);
	void injectProperty(const QMetaObject *metaObj, IMcBeanDefinition *beanDefinition);

private:
	static McIocContainer *m_container;

	IMcApplicationContext *m_applicationContext{ Q_NULLPTR };
	QMap<QString, QString> m_autowiredRegistry;	// ����������Ҫ�Զ�ע���bean��typeName��beanName

private:
	explicit McIocContainer(QObject *parent = 0);
};

#endif // !_MC_IOC_CONTAINER_H_