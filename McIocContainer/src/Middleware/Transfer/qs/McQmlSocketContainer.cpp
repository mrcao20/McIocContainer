#include "include/Middleware/Transfer/impl/qs/McQmlSocketContainer.h"

#include <QJSValue>
#include <QMap>
#include <QMetaMethod>
#include <QCoreApplication>
#include <QDebug>

#include "include/McIocBoot.h"
#include "include/ApplicationContext/IMcApplicationContext.h"
#include "include/Middleware/Transfer/impl/qs/McQmlSocket.h"
#include "include/Middleware/Transfer/impl/qs/McSession.h"
#include "include/Middleware/Transfer/impl/qs/McQmlSocketRunner.h"
#include "include/Middleware/Transfer/impl/qs/McInnerSocket.h"

MC_DECLARE_PRIVATE_DATA(McQmlSocketContainer)
QMap<QString, QSharedPointer<QObject>> sockets;
MC_DECLARE_PRIVATE_DATA_END()

McQmlSocketContainer::McQmlSocketContainer(QObject *parent)
    : QObject(parent)
    , MC_NEW_PRIVATE_DATA(McQmlSocketContainer)
{
}

McQmlSocketContainer::~McQmlSocketContainer() {
}

void McQmlSocketContainer::init(const QSharedPointer<McIocBoot> &boot) noexcept {
    MC_D(McQmlSocketContainer)
    auto appCtx = boot->getApplicationContext();
	auto beanNames = boot->getComponent(MC_QML_SOCKET);
    for (const auto &beanName : beanNames) {
        auto obj = appCtx->getBean(beanName);
        if(!obj) {
            qCritical() << QString("socket for named '%1' not exists").arg(beanName);
            continue;
        }
        d->sockets.insert(beanName, obj);
    }
}

McQmlSocket *McQmlSocketContainer::addConnect(const QString &uri) noexcept {
    auto qs = new McQmlSocket();
    
    addConnect(qs, uri);
    
    return qs;
}

McQmlSocket *McQmlSocketContainer::addConnect(const QString &uri, const QJSValue &data) noexcept {
    auto qs = new McQmlSocket();
    bool isSync = data.hasProperty("isOpenSync") ? data.property("isOpenSync").toBool() : false;
    if(data.hasProperty("onOpen"))
        qs->onOpen(data.property("onOpen"), isSync);
    isSync = data.hasProperty("isCloseSync") ? data.property("isCloseSync").toBool() : false;
    if(data.hasProperty("onClose"))
        qs->onClose(data.property("onClose"), isSync);
    isSync = data.hasProperty("isErrorSync") ? data.property("isErrorSync").toBool() : false;
    if(data.hasProperty("onError"))
        qs->onError(data.property("onError"), isSync);
    isSync = data.hasProperty("isMessageSync") ? data.property("isMessageSync").toBool() : false;
    if(data.hasProperty("onMessage"))
        qs->onMessage(data.property("onMessage"), isSync);
    
    addConnect(qs, uri);
    
    return qs;
}

void McQmlSocketContainer::addConnect(McQmlSocket *socket, const QString &uri) noexcept {
    MC_D(McQmlSocketContainer);
    
    QSharedPointer<McSession> session = QSharedPointer<McSession>::create();
    McQmlSocketRunner *runner = new McQmlSocketRunner();
    
    QSharedPointer<McInnerSocket> innerSocket;
    
    if(d->sockets.contains(uri)) {
        innerSocket = getMethods(d->sockets[uri]);
    }
    
    runner->setSocket(socket);
    runner->setSession(session);
    runner->setInnerSocket(innerSocket);
    runner->run();
    
    if(!innerSocket) {
        qApp->postEvent(runner, new SocketEvent(
                        SocketEvent::InnerSocketErrorEvent
                        , "not exists the socket for named: " + uri));
    }
}

QSharedPointer<McInnerSocket> McQmlSocketContainer::getMethods(const QSharedPointer<QObject> &bean) noexcept {
    if(!bean) {
        return QSharedPointer<McInnerSocket>();
    }
    
    McInnerSocketPtr innerSocket = McInnerSocketPtr::create();
    
    auto mo = bean->metaObject();
    for(int i = 0; i < mo->methodCount(); ++i) {
        auto index = i + mo->methodOffset();
        auto method = mo->method(index);
        QString tags = method.tag();
        if(tags.contains(MC_MACRO_STR(MC_ON_OPEN))) {
            innerSocket->setOnOpen(method);
        }else if(tags.contains(MC_MACRO_STR(MC_ON_CLOSE))) {
            innerSocket->setOnClose(method);
        }else if(tags.contains(MC_MACRO_STR(MC_ON_ERROR))) {
            innerSocket->setOnError(method);
        }else if(tags.contains(MC_MACRO_STR(MC_ON_MESSAGE))) {
            innerSocket->setOnMessage(method);
        }
    }
    
    innerSocket->setInnerSocketObj(bean);
    
    return innerSocket;
}
