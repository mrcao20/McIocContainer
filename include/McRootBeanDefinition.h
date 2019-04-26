/*******************************************************************
 <文件名>		McRootBeanDefinition.h
 <详细说明>		用于存放bean的相关数据
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#ifndef _MC_BEAN_DEFINITION_H_
#define _MC_BEAN_DEFINITION_H_

#include <QObject>
#include "IMcBeanDefinition.h"

#include <qvariant.h>

#include "McMacroGlobal.h"

class McRootBeanDefinition 
	: public QObject
	, MC_IMPLEMENTS IMcBeanDefinition {
	Q_OBJECT;

public:
	explicit McRootBeanDefinition(QObject *parent = 0)
		: QObject(parent){}
	virtual ~McRootBeanDefinition() {
		MC_SAFE_DELETE(m_bean);
		MC_SAFE_DELETE(m_beanMetaObject);
	}

	QObject *getBean() const Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { return m_bean; }
	void setBean(QObject *bean) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { m_bean = bean; }

	const QMetaObject *getBeanMetaObject() const Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { return m_beanMetaObject; }
	void setBeanMetaObject(QMetaObject *o) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { m_beanMetaObject = o; }

	QString getClassName() const Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { return m_className; }
	void setClassName(const QString &name) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE {
		m_className = name;
		m_beanMetaObject = QMetaType::metaObjectForType(QMetaType::type(m_className.toLocal8Bit().data()));
	}

	QVariantHash getProperties() const Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { return m_properties; }
	void addProperty(const QString &name, const QVariant &value) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE {
		m_properties.insert(name, value);
	}

private:
	QObject *m_bean{ Q_NULLPTR };										// bean
	const QMetaObject *m_beanMetaObject{ Q_NULLPTR };					// bean的MetaObject对象
	QString m_className;												// bean的类全限定名称
	QVariantHash m_properties;											// bean的属性集合
};

#endif // !_MC_BEAN_DEFINITION_H_