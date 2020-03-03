/*******************************************************************
 <文件名>		McRootBeanDefinition.h
 <详细说明>		用于存放bean的相关数据
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#pragma once

#include <QObject>
#include "../IMcBeanDefinition.h"

#include "../../McMacroGlobal.h"

class McRootBeanDefinition 
	: public QObject
	, MC_IMPLEMENTS IMcBeanDefinition {
    Q_OBJECT

public:
    explicit McRootBeanDefinition(QObject *parent = nullptr)
		: QObject(parent){}

    ~McRootBeanDefinition() override {
        // 现在beanDefinition的所有属性均使用栈对象或QSharedPointer，所以不再需要手动析构
//        QHashIterator<decltype (m_properties)::key_type, decltype (m_properties)::mapped_type> iterator(m_properties);
//        while (iterator.hasNext()) {
//            auto item = iterator.next();
//            auto value = item.value();
//            auto obj = value.value<QObject*>();
//            if(obj)
//                obj->deleteLater();
//        }
    }

    QVariant getBean() const Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { return m_bean; }
    void setBean(const QVariant& bean) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { m_bean = bean; }

    bool isSingleton() const noexcept override {return m_isSingleton;}
    void setSingleton(bool val) noexcept override {m_isSingleton = val;}

    const QMetaObject *getBeanMetaObject() const Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { return m_beanMetaObject; }
    void setBeanMetaObject(QMetaObject *o) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { m_beanMetaObject = o; }

    QString getClassName() const Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { return m_className; }
    void setClassName(const QString &name) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE {
            m_className = name;
            m_beanMetaObject = QMetaType::metaObjectForType(QMetaType::type(m_className.toLocal8Bit().data()));
    }

    QString getPluginPath() const Q_DECL_NOEXCEPT Q_DECL_OVERRIDE {
        return m_pluginPath;
    }
    void setPluginPath(const QString &path) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE {
        m_pluginPath = path;
    }

    QVariantHash getProperties() const Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { return m_properties; }
    void addProperty(const QString &name, const QVariant &value) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE {
        m_properties.insert(name, value);
    }
    
    QVariantList getConnectors() const Q_DECL_NOEXCEPT Q_DECL_OVERRIDE {return m_connectors;}
    void addConnector(const QVariant &val) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE {
        m_connectors.append(val);
    }

private:
    QVariant m_bean;                                                    // 包含bean的QVariant。此对象不再删除该bean
    bool m_isSingleton{true};                                           // 该bean是否是单例，默认是
    const QMetaObject *m_beanMetaObject{ Q_NULLPTR };                   // bean的MetaObject对象
    QString m_className;												// bean的类全限定名称
    QString m_pluginPath;                                               // bean的插件路径
    QVariantHash m_properties;											// bean的属性集合
    QVariantList m_connectors;                                          // bean中需要连接的信号槽
};

MC_DECLARE_POINTER(McRootBeanDefinition)
