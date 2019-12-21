/*******************************************************************
 <�ļ���>		IMcBeanDefinition.h
 <��ϸ˵��>		�ӿڣ��ṩbeanDefinition�Ĺ���
 <��   ��>		mrcao
 <��   ��>		2019/4/3
********************************************************************/

#pragma once

#include "McMacroGlobal.h"

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
	// ʹ�ô˺�������className֮�󣬻��Զ�����QMetaObject
	virtual void setClassName(const QString &name) Q_DECL_NOEXCEPT = 0;

    virtual QString getPluginPath() const Q_DECL_NOEXCEPT = 0;
    virtual void setPluginPath(const QString &path) Q_DECL_NOEXCEPT = 0;

	virtual QVariantHash getProperties() const Q_DECL_NOEXCEPT = 0;
	// ����QVariant������ʱ���Զ�ɾ�������Ķ������Ըö��������ø�����
	virtual void addProperty(const QString &name, const QVariant &value) Q_DECL_NOEXCEPT = 0;
};
