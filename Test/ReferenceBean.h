#pragma once

#include <QObject>

#include "HelloWorld.h"
#include "a.h"

#include <qdebug.h>
#include <qlist.h>
#include <QEnableSharedFromThis>
#include <QJsonObject>
#include <QQmlListProperty>

#include "McMacroGlobal.h"
#include "IRR.h"
#include "ListModel.h"
//#include "PropertyParser/IMcPropertyParserCollection.h"

class ReferenceBean : public QObject, public IRR, public QEnableSharedFromThis<ReferenceBean> {
    Q_OBJECT
    Q_CLASSINFO(MC_COMPONENT, MC_CONTROLLER)
    Q_PROPERTY(QSharedPointer<ListModel> listModel MEMBER m_listModel USER true)
    Q_PROPERTY(QSharedPointer<IHelloWorld> helloWorld READ getHello WRITE setHello USER true)
    Q_PROPERTY(QSharedPointer<A> a MEMBER m_a USER true)
    Q_PROPERTY(QList<QSharedPointer<IHelloWorld>> listData0 MEMBER m_list0)
    Q_PROPERTY(QList<QVariant> listData MEMBER m_list)
//    Q_PROPERTY(QList<QSharedPointer<IMcPropertyParserCollection>> pluginList MEMBER m_pluginList)
//    Q_PROPERTY(QMap<QString, QString> mapData MEMBER m_mapData);
//    Q_PROPERTY(QMap<QString, QSharedPointer<IHelloWorld>> mapData1 MEMBER m_mapData1);
    Q_PROPERTY(QVariant text MEMBER m_text)
    MC_DECL_STATIC(ReferenceBean)
    MC_DEFINE_TYPELIST(QObject, MC_TYPELIST(IRR))

public:
	Q_INVOKABLE explicit ReferenceBean(QObject *parent = nullptr);
	~ReferenceBean() override;

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
    
    Q_INVOKABLE void aaa(const QString &str, const QSharedPointer<HelloWorld> &h) noexcept;
    Q_INVOKABLE QJsonObject b() noexcept;
    Q_INVOKABLE QObject *o() noexcept;
    Q_INVOKABLE QAbstractItemModel *getModel() noexcept;
    Q_INVOKABLE QMap<QString, QVariant> getModels() noexcept;

	/*QList<int> getList() { return m_list; }
	void setList(QList<int> hello) {
		qDebug() << "aaa";
		m_list = hello;
	}*/

    QSharedPointer<IHelloWorld> getHello() { return m_hello; }
    void setHello(const QSharedPointer<IHelloWorld>& hello) {
		m_hello = hello;
	}
    
signals:
    void signal_bean(const QSharedPointer<A>&);

public:
    QSharedPointer<IHelloWorld> m_hello{ Q_NULLPTR };
    QSharedPointer<HelloWorld> m_hello2{ Q_NULLPTR };
    QSharedPointer<A> m_a;
    //QList<IHelloWorld *> m_list;
    QList<QVariant> m_list;
    QList<QSharedPointer<IHelloWorld>> m_list0;
//    QList<QSharedPointer<IMcPropertyParserCollection>> m_pluginList;
    QMap<QString, QString> m_mapData;
    QMap<QString, QSharedPointer<IHelloWorld>> m_mapData1;
    QSharedPointer<ListModel> m_listModel;
    QVariant m_text;
};

MC_DECLARE_METATYPE(ReferenceBean)
