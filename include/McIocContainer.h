/*******************************************************************
 <�ļ���>		McIocContainer.h
 <��ϸ˵��>		ȫ��Ψһ�������������Զ�ע�롣
				����ʼʱ�������initContainer������ʼ�������������Զ�ע�뽫����ɹ���
				����C++��̬������ʼ��˳��ȷ�������Դ˴��ĵ���ģʽʹ��˫�ؼ�����
 <��   ��>		mrcao
 <��   ��>		2019/4/7
********************************************************************/

#pragma once

#include <QObject>
#include "McMacroGlobal.h"

#include <QHash>
#include <QSharedPointer>

class IMcApplicationContext;
class IMcBeanDefinition;

class MCIOCCONTAINER_EXPORT McIocContainer : public QObject {
    Q_OBJECT

public:
    ~McIocContainer();

    static McIocContainer *getInstance();

    // ��ʼ���������˺������̰߳�ȫ�������ظ���ʼ��
    void initContainer();

    void insertRegistry(const QString &typeName, const QString &beanName, bool isSingleton = true) noexcept;

    // ��ȡ�����齨����ΪcomponentType��bean������
    QList<QString> getComponent(const QString &componentType) noexcept;
    // �����Ԫ�������������Ƿ�Ϊtype
    bool isComponentType(const QMetaObject *metaObj, const QString &type) noexcept;

    QSharedPointer<IMcApplicationContext> getApplicationContext() {
            return m_applicationContext;
    }

private:
    void inject(const QString& beanName, const QSharedPointer<IMcBeanDefinition>& beanDefinition);
    void injectProperty(const QMetaObject *metaObj, const QSharedPointer<IMcBeanDefinition>& beanDefinition);

private:
    static McIocContainer *m_container;

    QSharedPointer<IMcApplicationContext> m_applicationContext;
    QHash<QString, QSharedPointer<IMcBeanDefinition>> m_autowiredRegistry;	// ����������Ҫ�Զ�ע���bean��beanName��BeanDefinition

private:
    explicit McIocContainer(QObject *parent = nullptr);
};
