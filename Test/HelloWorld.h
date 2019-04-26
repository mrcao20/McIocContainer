#pragma once

#include <qobject.h>
#include "IHelloWorld.h"

#include <qdebug.h>

#include "McMacroGlobal.h"
#include "McBeanGlobal.h"

class HelloWorld : public QObject, public IHelloWorld {
	Q_OBJECT;
	Q_PROPERTY(bool text READ getText WRITE setText USER false);
	Q_PROPERTY(QMap<int, QString> map READ getMap WRITE setMap);
	Q_PROPERTY(QSet<int> list READ getList WRITE setList);
	MC_DECL_STATIC(HelloWorld);

public:
	Q_INVOKABLE explicit HelloWorld(QObject *parent = 0);

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

	bool getText() { return m_text; }
	void setText(const bool &text) {
		m_text = text;
	}

private:
	bool m_text;
	QMap<int, QString> m_map;
	QSet<int> m_list;

};

Q_DECLARE_METATYPE(HelloWorld *)