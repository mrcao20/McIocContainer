/*******************************************************************
 <文件名>		McIocContainer.h
 <详细说明>		全局唯一的容器，用于自动注入。
				程序开始时必须调用initContainer函数初始化容器，否则自动注入将不会成功。
				由于C++静态变量初始化顺序不确定，所以此处的单例模式使用双重加锁。
 <作   者>		mrcao
 <日   期>		2019/4/7
********************************************************************/

#pragma once

#include <QObject>
#include "McMacroGlobal.h"

#include <QHash>

class IMcApplicationContext;
class IMcBeanDefinition;

class MCIOCCONTAINER_EXPORT McIocContainer : public QObject {
    Q_OBJECT

public:
    ~McIocContainer();

    static McIocContainer *getInstance();

    // 初始化容器，此函数非线程安全，请勿重复初始化
    void initContainer();

    void insertRegistry(const QString &typeName, const QString &beanName, bool isSingleton = true) noexcept;

    // 获取所有组建类型为componentType的bean的名称
    QList<QString> getComponent(const QString &componentType) noexcept;
    // 传入的元对象的组件类型是否为type
    bool isComponentType(const QMetaObject *metaObj, const QString &type) noexcept;

    IMcApplicationContext *getApplicationContext() {
            return m_applicationContext;
    }

private:
    void inject(const QString& beanName, const QSharedPointer<IMcBeanDefinition>& beanDefinition);
    void injectProperty(const QMetaObject *metaObj, const QSharedPointer<IMcBeanDefinition>& beanDefinition);

private:
    static McIocContainer *m_container;

    IMcApplicationContext *m_applicationContext{ Q_NULLPTR };
    QHash<QString, QSharedPointer<IMcBeanDefinition>> m_autowiredRegistry;	// 用来保存需要自动注入的bean的beanName和BeanDefinition

private:
    explicit McIocContainer(QObject *parent = nullptr);
};
