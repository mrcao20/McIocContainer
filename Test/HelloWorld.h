#pragma once

#include <qobject.h>
#include "IHelloWorld.h"
#include "a.h"

#include <qdebug.h>

class HelloWorld : public QObject, public IHelloWorld {
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText USER false)
//    Q_PROPERTY(QMap<int, QString> map READ getMap WRITE setMap)
    Q_PROPERTY(QSet<int> list READ getList WRITE setList)
    MC_DECL_STATIC(HelloWorld)
    Q_CLASSINFO("Component", "Controller")
    MC_DEFINE_TYPELIST(QObject, MC_TYPELIST(IHelloWorld))

public:
	Q_INVOKABLE explicit HelloWorld(QObject *parent = 0);
    ~HelloWorld();

    Q_INVOKABLE MC_AUTOWIRED void say() {
		qDebug() << m_text;
	}

	QSet<int> getList() { return m_list; }
	void setList(const QSet<int> &text) {
		m_list = text;
	}

	QMap<int, QString> getMap() { return m_map; }
	void setMap(const QMap<int, QString> &text) {
		m_map = text;
	}

    QString getText() { return m_text; }
    void setText(const QString &text) {
		m_text = text;
	}
    
public slots:
    void slot_hello(const QSharedPointer<A> &a);

private:
    QString m_text;
	QMap<int, QString> m_map;
	QSet<int> m_list;

};

class AAA {
public:
    HelloWorld *h;
};

MC_DECLARE_POINTER(HelloWorld)
MC_DECLARE_METATYPE(HelloWorld)
