#pragma once

#include <QObject>

#include "IHelloWorld.h"

#include <qdebug.h>
#include <qlist.h>
#include <QEnableSharedFromThis>

#include "BeanFactory/McBeanGlobal.h"
#include "IRR.h"

class ReferenceBean : public QObject, public IRR, public QEnableSharedFromThis<ReferenceBean> {
    Q_OBJECT
    Q_PROPERTY(QSharedPointer<IHelloWorld> helloWorld READ getHello WRITE setHello USER true);
    Q_PROPERTY(QList<QVariant> listData MEMBER m_list);
    Q_PROPERTY(QVariant text MEMBER m_text);
    MC_DECL_STATIC(ReferenceBean)
    MC_DEFINE_TYPELIST(QObject, MC_TYPELIST(IRR))

public:
	Q_INVOKABLE explicit ReferenceBean(QObject *parent = 0);
	~ReferenceBean();

    void say() override {
        qDebug() << m_hello << m_list << m_text;
        if(!m_list.isEmpty()) {
            auto i1 = m_list.at(0);
            auto h = i1.value<QSharedPointer<IHelloWorld>>();
            qDebug() << h;
            h->say();
        }
        //m_hello->say();
	}

	/*QList<int> getList() { return m_list; }
	void setList(QList<int> hello) {
		qDebug() << "aaa";
		m_list = hello;
	}*/

    QSharedPointer<IHelloWorld> getHello() { return m_hello; }
    void setHello(const QSharedPointer<IHelloWorld>& hello) {
		m_hello = hello;
	}

private:
    QSharedPointer<IHelloWorld> m_hello{ Q_NULLPTR };
    //QList<IHelloWorld *> m_list;
    QList<QVariant> m_list;
    QVariant m_text;
};

MC_DECLARE_METATYPE(ReferenceBean)
