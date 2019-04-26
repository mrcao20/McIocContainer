/*******************************************************************
 <文件名>		McBeanReference.h
 <详细说明>		用于存放bean的引用的相关数据
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#ifndef _MC_BEAN_REFERENCE_H_
#define _MC_BEAN_REFERENCE_H_

#include <qobject.h>
#include "McMacroGlobal.h"

class MCIOCCONTAINER_EXPORT McBeanReference : public QObject {
	Q_OBJECT

public:
	// 构造器， 必须包含一个bean名称
	explicit McBeanReference(const QString &name, QObject *parent = 0)
		: QObject(parent)
		, m_name(name){}
	virtual ~McBeanReference() = default;

	QString getName() { return m_name; }
	void setName(const QString &name) { m_name = name; }

	QObject *getBean() { return m_bean; }
	void setBean(QObject *bean) { m_bean = bean; }

private:
	QString m_name;						// 被引用bean的名称
	QObject *m_bean{ Q_NULLPTR };		// 被引用bean的对象
};

#endif // !_MC_BEAN_REFERENCE_H_