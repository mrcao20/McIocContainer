#include "include/McIocBoot.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QJSValue>
#include <QDebug>

#include "include/McMacroGlobal.h"
#include "include/BeanFactory/McBeanGlobal.h"
#include "include/ApplicationContext/impl/McAnnotationApplicationContext.h"
#include "include/BeanDefinition/IMcBeanDefinition.h"
#include "include/Middleware/Transfer/impl/McControllerContainer.h"
#include "include/Middleware/Transfer/impl/McModelContainer.h"
#include "include/Middleware/Transfer/impl/qs/McQmlSocketContainer.h"
#include "include/Middleware/Transfer/impl/McRequestor.h"

MC_DECLARE_PRIVATE_DATA(McIocBoot)
QSharedPointer<McAnnotationApplicationContext> context;
MC_DECLARE_PRIVATE_DATA_END()

McIocBoot::McIocBoot(QObject *parent)
    : QObject(parent)
    , MC_NEW_PRIVATE_DATA(McIocBoot)
{
}

McIocBoot::~McIocBoot() {
}

int McIocBoot::run(int argc, char *argv[], const function<void(QJSEngine *)> &func) noexcept {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    
    McIocBootPtr boot = McIocBootPtr::create();
    boot->initBoot();
    
    McControllerContainerPtr controllerContainer = McControllerContainerPtr::create();
    controllerContainer->init(boot);
    
    McModelContainerPtr modelContainer = McModelContainerPtr::create();
    modelContainer->init(boot);
    
    McQmlSocketContainerPtr socketContainer = McQmlSocketContainerPtr::create();
    socketContainer->init(boot);
    
    McRequestor *requestor = new McRequestor(); // 不需要设置父对象
    requestor->setControllerContainer(controllerContainer);
    requestor->setSocketContainer(socketContainer);

    QQmlApplicationEngine engine;
    // engine的newQObject函数会将其参数所有权转移到其返回的QJSValue中
    QJSValue jsObj = engine.newQObject(requestor);
    engine.globalObject().setProperty("$", jsObj);
    engine.importModule(":/Requestor.js");
    
    func(&engine);
    
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

void McIocBoot::initBoot() noexcept {
    MC_D(McIocBoot);
    if (d->context) {
		qInfo() << "The container has been initialized";
		return;
	}
    Mc::Ioc::mcInitContainer();
    d->context = QSharedPointer<McAnnotationApplicationContext>::create();
    d->context->refresh();  // 预加载bean
}

QSharedPointer<IMcApplicationContext> McIocBoot::getApplicationContext() const noexcept {
    MC_D(McIocBoot);
    return d->context;
}

QList<QString> McIocBoot::getComponent(const QString &componentType) noexcept {
    auto context = getApplicationContext();
	if (!context) {
		qCritical() << "Please call initContainer to initialize container first";
		return QList<QString>();
	}
	QList<QString> components;
    QMap<QString, QSharedPointer<IMcBeanDefinition>> beanDefinitions = context->getBeanDefinitions();
	for (auto itr = beanDefinitions.cbegin(); itr != beanDefinitions.cend(); ++itr) {
		auto beanDefinition = itr.value();
		if (!isComponentType(beanDefinition->getBeanMetaObject(), componentType))
			continue;
		components.append(itr.key());
	}
	return components;
}

bool McIocBoot::isComponentType(const QMetaObject *metaObj, const QString &type) noexcept {
    if(!metaObj) {
        return false;
    }
	int classInfoCount = metaObj->classInfoCount();
	for (int i = 0; i < classInfoCount; ++i) {
		auto classInfo = metaObj->classInfo(i);
		if (qstrcmp(classInfo.name(), "Component") != 0)
			continue;
		return classInfo.value() == type;
	}
	return false;
}
