#pragma once

#include <QObject>

#include "IHelloWorld.h"

#include <qdebug.h>
#include <qlist.h>

#include "McBeanGlobal.h"

class ReferenceBean : public QObject {
	Q_OBJECT;
    Q_PROPERTY(IHelloWorld *helloWorld READ getHello WRITE setHello USER true);
	Q_PROPERTY(QList<IHelloWorld *> listData MEMBER m_list);
	MC_DECL_STATIC(ReferenceBean);

public:
	Q_INVOKABLE explicit ReferenceBean(QObject *parent = 0);
	~ReferenceBean();

	void say() {
		qDebug() << m_hello << m_list;
	}

	/*QList<int> getList() { return m_list; }
	void setList(QList<int> hello) {
		qDebug() << "aaa";
		m_list = hello;
	}*/

	IHelloWorld *getHello() { return m_hello; }
	void setHello(IHelloWorld *hello) {
		m_hello = hello;
	}

private:
	IHelloWorld *m_hello{ Q_NULLPTR };
	QList<IHelloWorld *> m_list;
};

Q_DECLARE_METATYPE(ReferenceBean *);
