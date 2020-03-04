/*******************************************************************
 <文件名>		IMcBeanDefinition.h
 <详细说明>		接口，提供beanDefinition的功能
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#pragma once

#include "../McMacroGlobal.h"

#include <qstring.h>
#include <qvariant.h>

QT_BEGIN_NAMESPACE
class QObject;
QT_END_NAMESPACE

MC_INTERFACE IMcBeanDefinition {

public:
	virtual ~IMcBeanDefinition() = default;

    virtual QVariant getBean() const Q_DECL_NOEXCEPT = 0;
    virtual void setBean(const QVariant& bean) Q_DECL_NOEXCEPT = 0;

    virtual bool isSingleton() const noexcept = 0;
    virtual void setSingleton(bool val) noexcept = 0;

	virtual const QMetaObject *getBeanMetaObject() const Q_DECL_NOEXCEPT = 0;
	virtual void setBeanMetaObject(QMetaObject *o) Q_DECL_NOEXCEPT = 0;

	virtual QString getClassName() const Q_DECL_NOEXCEPT = 0;
	// 使用此函数设置className之后，会自动生成QMetaObject
	virtual void setClassName(const QString &name) Q_DECL_NOEXCEPT = 0;

    virtual QString getPluginPath() const Q_DECL_NOEXCEPT = 0;
    virtual void setPluginPath(const QString &path) Q_DECL_NOEXCEPT = 0;

	virtual QVariantHash getProperties() const Q_DECL_NOEXCEPT = 0;
	// 由于QVariant在析构时会自动删除包含的对象，所以该对象不用设置父对象
	virtual void addProperty(const QString &name, const QVariant &value) Q_DECL_NOEXCEPT = 0;
    
    virtual QVariantList getConnectors() const Q_DECL_NOEXCEPT = 0;
    virtual void addConnector(const QVariant &val) Q_DECL_NOEXCEPT = 0;
};
