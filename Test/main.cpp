#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "McIocBoot.h"
#include <QDebug>

#include "ReferenceBean.h"
#include "a.h"
#include "ApplicationContext/impl/McXmlApplicationContext.h"
#include "PropertyParser/IMcPropertyParserCollection.h"
#include "QmlSocketTest.h"

int main(int argc, char *argv[])
{
    
    return McIocBoot::run(argc, argv);
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

//    QGuiApplication app(argc, argv);
 
//    auto mo = &QmlSocketTest::staticMetaObject;
//    int index = mo->indexOfMethod("testFunc()");
//    auto mm = mo->method(index);
//    qDebug() << index << mm.typeName() << mm.tag();
    
//    QQmlApplicationEngine engine;
    
//    const QUrl url(QStringLiteral("qrc:/main.qml"));
//    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
//                     &app, [url](QObject *obj, const QUrl &objUrl) {
//        if (!obj && url == objUrl)
//            QCoreApplication::exit(-1);
//    }, Qt::QueuedConnection);
//    engine.load(url);

//    return app.exec();
}
