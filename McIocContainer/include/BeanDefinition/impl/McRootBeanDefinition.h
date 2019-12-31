/*******************************************************************
 <�ļ���>		McRootBeanDefinition.h
 <��ϸ˵��>		���ڴ��bean���������
 <��   ��>		mrcao
 <��   ��>		2019/4/3
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
        QHashIterator<decltype (m_properties)::key_type, decltype (m_properties)::mapped_type> iterator(m_properties);
        while (iterator.hasNext()) {
            auto item = iterator.next();
            auto value = item.value();
            auto obj = value.value<QObject*>();
            if(obj)
                obj->deleteLater();
        }
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

private:
    QVariant m_bean;                                                    // ����bean��QVariant���˶�����ɾ����bean
    bool m_isSingleton{true};                                           // ��bean�Ƿ��ǵ�����Ĭ����
    const QMetaObject *m_beanMetaObject{ Q_NULLPTR };                   // bean��MetaObject����
    QString m_className;												// bean����ȫ�޶�����
    QString m_pluginPath;                                               // bean�Ĳ��·��
    QVariantHash m_properties;											// bean�����Լ���
};
