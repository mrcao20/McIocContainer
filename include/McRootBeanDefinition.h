/*******************************************************************
 <�ļ���>		McRootBeanDefinition.h
 <��ϸ˵��>		���ڴ��bean���������
 <��   ��>		mrcao
 <��   ��>		2019/4/3
********************************************************************/

#ifndef _MC_BEAN_DEFINITION_H_
#define _MC_BEAN_DEFINITION_H_

#include <QObject>
#include "IMcBeanDefinition.h"

#include <qvariant.h>
#include <qpointer.h>

#include "McMacroGlobal.h"

class McRootBeanDefinition 
	: public QObject
	, MC_IMPLEMENTS IMcBeanDefinition {
	Q_OBJECT;

public:
	explicit McRootBeanDefinition(QObject *parent = 0)
		: QObject(parent){}
	virtual ~McRootBeanDefinition() {
		MC_SAFE_DELETE_QPOINTER(m_bean);
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

    QString getPluginPath() const Q_DECL_NOEXCEPT {
        return m_pluginPath;
    }
    void setPluginPath(const QString &path) Q_DECL_NOEXCEPT {
        m_pluginPath = path;
    }

	QVariantHash getProperties() const Q_DECL_NOEXCEPT Q_DECL_OVERRIDE { return m_properties; }
	void addProperty(const QString &name, const QVariant &value) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE {
		m_properties.insert(name, value);
	}

private:
	QPointer<QObject> m_bean;											// bean
	const QMetaObject *m_beanMetaObject{ Q_NULLPTR };					// bean��MetaObject����
	QString m_className;												// bean����ȫ�޶�����
    QString m_pluginPath;                                               // bean�Ĳ��·��
	QVariantHash m_properties;											// bean�����Լ���
};

#endif // !_MC_BEAN_DEFINITION_H_
