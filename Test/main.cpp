#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "McIocBoot.h"
#include <QDebug>
#include <QThread>
#include <QtConcurrent>
#include <QDateTime>

#include "ReferenceBean.h"
#include "a.h"
#include "ApplicationContext/impl/McXmlApplicationContext.h"
#include "PropertyParser/IMcPropertyParserCollection.h"
#include "QmlSocketTest.h"
#include "MacroTest.h"

int main(int argc, char *argv[])
{
/*    QVariant var;
    QSharedPointer<ReferenceBean> r(new ReferenceBean());
    var.setValue(r);
    auto i = var.value<QSharedPointer<IRR>>();
    qDebug() << i << QThread::currentThread();
    return McIocBoot::run(argc, argv)*/;
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    
//    auto start = QDateTime::currentMSecsSinceEpoch();
//    QHash<QPair<int, int>, QObject *> h;
//    for(int i = 0; i < 1000000; ++i) {
//        auto o = new QObject();
//        o->setObjectName(QString::number(i));
//        h.insert(QPair<int, int>(i, i), o);
//    }
//    auto end = QDateTime::currentMSecsSinceEpoch();
//    qDebug() << start << end << (end - start);
//    start = QDateTime::currentMSecsSinceEpoch();
//    for(int i = 0; i < 100000; ++i) {
//        auto o = h.value(QPair<int, int>(90000, 90000));
//    }
////    QThread::msleep(1000);
//    end = QDateTime::currentMSecsSinceEpoch();
//    qDebug() << start << end << (end - start);

    QGuiApplication app(argc, argv);
    
//    MacroTest t;
    
    qDebug() << QThread::currentThread();
    Mc::Ioc::mcInitContainer();
    auto tt = QThread::currentThread();
    QSharedPointer<IMcApplicationContext> appCon = nullptr;
    auto f = QtConcurrent::run([&appCon, tt]() {
        appCon = QSharedPointer<McXmlApplicationContext>::create(QStringList() << ":/myspring.xml" << ":/xmltest2.xml");
        appCon->refresh(tt);
    });
    f.waitForFinished();
    auto r = appCon->getBean("aaa").objectCast<ReferenceBean>();
    qDebug() << "---------" << r->thread() << r->getHello().dynamicCast<HelloWorld>()->thread();
    
    QQmlApplicationEngine engine;
    
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
