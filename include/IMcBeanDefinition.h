/*******************************************************************
 <�ļ���>		IMcBeanDefinition.h
 <��ϸ˵��>		�ӿڣ��ṩbeanDefinition�Ĺ���
 <��   ��>		mrcao
 <��   ��>		2019/4/3
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
	// ʹ�ô˺�������className֮�󣬻��Զ�����QMetaObject
	virtual void setClassName(const QString &name) Q_DECL_NOEXCEPT = 0;

	virtual QVariantHash getProperties() const Q_DECL_NOEXCEPT = 0;
	// ����QVariant������ʱ���Զ�ɾ�������Ķ������Ըö��������ø�����
	virtual void addProperty(const QString &name, const QVariant &value) Q_DECL_NOEXCEPT = 0;
};

#endif // !_I_MC_BEAN_DEFINITION_H_

