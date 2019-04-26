/*******************************************************************
 <�ļ���>		McBeanReference.h
 <��ϸ˵��>		���ڴ��bean�����õ��������
 <��   ��>		mrcao
 <��   ��>		2019/4/3
********************************************************************/

#ifndef _MC_BEAN_REFERENCE_H_
#define _MC_BEAN_REFERENCE_H_

#include <qobject.h>
#include "McMacroGlobal.h"

class MCIOCCONTAINER_EXPORT McBeanReference : public QObject {
	Q_OBJECT

public:
	// �������� �������һ��bean����
	explicit McBeanReference(const QString &name, QObject *parent = 0)
		: QObject(parent)
		, m_name(name){}
	virtual ~McBeanReference() = default;

	QString getName() { return m_name; }
	void setName(const QString &name) { m_name = name; }

	QObject *getBean() { return m_bean; }
	void setBean(QObject *bean) { m_bean = bean; }

private:
	QString m_name;						// ������bean������
	QObject *m_bean{ Q_NULLPTR };		// ������bean�Ķ���
};

#endif // !_MC_BEAN_REFERENCE_H_