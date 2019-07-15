/*******************************************************************
 <文件名>		IMcBeanDefinition.h
 <详细说明>		接口，提供beanDefinition的功能
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#ifndef _I_MC_BEAN_DEFINITION_H_
#define _I_MC_BEAN_DEFINITION_H_

#include "McMacroGlobal.h"

#include <qstring.h>
#include <qvariant.h>

QT_BEGIN_NAMESPACE
class QObject;
QT_END_NAMESPACE

MC_INTERFACE IMcBeanDefinition {

public:
	virtual ~IMcBeanDefinition() = default;

	virtual QObject *getBean() const Q_DECL_NOEXCEPT = 0;
	virtual void setBean(QObject *bean) Q_DECL_NOEXCEPT = 0;

	virtual const QMetaObject *getBeanMetaObject() const Q_DECL_NOEXCEPT = 0;
	virtual void setBeanMetaObject(QMetaObject *o) Q_DECL_NOEXCEPT = 0;

	virtual QString getClassName() const Q_DECL_NOEXCEPT = 0;
	// 使用此函数设置className之后，会自动生成QMetaObject
	virtual void setClassName(const QString &name) Q_DECL_NOEXCEPT = 0;

	virtual QVariantHash getProperties() const Q_DECL_NOEXCEPT = 0;
	// 由于QVariant在析构时会自动删除包含的对象，所以该对象不用设置父对象
	virtual void addProperty(const QString &name, const QVariant &value) Q_DECL_NOEXCEPT = 0;
};

#endif // !_I_MC_BEAN_DEFINITION_H_

