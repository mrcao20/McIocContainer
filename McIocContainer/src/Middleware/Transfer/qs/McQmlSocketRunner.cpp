#include "include/Middleware/Transfer/impl/qs/McQmlSocketRunner.h"

#include <QThread>
#include <QJSValue>
#include <QCoreApplication>

#include "include/Middleware/Transfer/impl/qs/McSession.h"
#include "include/Middleware/Transfer/impl/qs/McQmlSocket.h"
#include "include/Middleware/Transfer/impl/qs/McInnerSocket.h"

SocketEvent::SocketEvent(int type, const QVariant &data)
    : QEvent(static_cast<QEvent::Type>(type))
    , m_data(data)
{}

SocketEvent::~SocketEvent() {
}

MC_DECLARE_PRIVATE_DATA(McQmlSocketRunner)
QThread thread;
McQmlSocket *socket;
QSharedPointer<McSession> session;
McInnerSocketPtr innerSocket;
MC_DECLARE_PRIVATE_DATA_END()

McQmlSocketRunner::McQmlSocketRunner(QObject *parent)
    : QObject(parent)
    , MC_NEW_PRIVATE_DATA(McQmlSocketRunner)
{
    MC_D(McQmlSocketRunner);
    moveToThread(&d->thread);
    d->thread.start();
}

McQmlSocketRunner::~McQmlSocketRunner() {
    MC_D(McQmlSocketRunner);
    d->thread.quit();
    // 由于当前对象本身就是处于另外的线程，所以这里直接使用死循环等待线程结束
    while(!d->thread.isFinished()) {
        QThread::msleep(100);
    }
}

void McQmlSocketRunner::setSocket(McQmlSocket *socket) noexcept {
    MC_D(McQmlSocketRunner);
    d->socket = socket;
}

void McQmlSocketRunner::setSession(const QSharedPointer<McSession> &session) noexcept {
    MC_D(McQmlSocketRunner);
    d->session = session;
}

void McQmlSocketRunner::setInnerSocket(const QSharedPointer<McInnerSocket> &innerSocket) noexcept {
    MC_D(McQmlSocketRunner);
    d->innerSocket = innerSocket;
}

// 全部采用直接连接，然后发送事件给自身，让线程回到自身线程再处理，同时每个请求都需要根据请求先后顺序执行
void McQmlSocketRunner::run() noexcept {
    MC_D(McQmlSocketRunner);
    
    connect(d->socket, &McQmlSocket::send, this, [this](const QJSValue &msg){
        QVariant var;
        var.setValue(msg);
        qApp->postEvent(this, new SocketEvent(SocketEvent::QmlSocketSendEvent, var));
    }, Qt::DirectConnection);
    connect(d->socket, &McQmlSocket::close, this, [this](){
        qApp->postEvent(this, new SocketEvent(SocketEvent::QmlSocketCloseEvent, ""));
    }, Qt::DirectConnection);
    
    connect(d->session.data(), &McSession::signal_send, this, [this](const QVariant &msg){
        qApp->postEvent(this, new SocketEvent(SocketEvent::InnerSocketSendEvent, msg));
    }, Qt::DirectConnection);
    connect(d->session.data(), &McSession::close, this, [this](){
        qApp->postEvent(this, new SocketEvent(SocketEvent::InnerSocketCloseEvent, ""));
    }, Qt::DirectConnection);
    
    if(d->innerSocket) {
        qApp->postEvent(this, new SocketEvent(SocketEvent::SocketInitEvent, ""));
    }
}

void McQmlSocketRunner::customEvent(QEvent *event) {
    MC_D(McQmlSocketRunner);
    
    int type = event->type();
    switch (type) {
    case SocketEvent::SocketInitEvent:
        d->socket->opened();
        d->innerSocket->opened(d->session);
        break;
    case SocketEvent::QmlSocketErrorEvent: {
        auto e = static_cast<SocketEvent *>(event);
        d->innerSocket->errored(d->session, e->data().toString());
        this->deleteLater();
        break;
    }
    case SocketEvent::QmlSocketSendEvent: {
        auto e = static_cast<SocketEvent *>(event);
        QJSValue msg = e->data().value<QJSValue>();
        QVariant var;
        if(msg.isQObject()) {
            var.setValue(msg.toQObject());
        }else{
            var = msg.toVariant();
        }
        d->innerSocket->receivedMsg(d->session, var);
        break;
    }
    case SocketEvent::QmlSocketCloseEvent:
        d->innerSocket->closed(d->session);
        this->deleteLater();
        break;
    case SocketEvent::InnerSocketErrorEvent: {
        auto e = static_cast<SocketEvent *>(event);
        d->socket->errored(e->data().toString());
        this->deleteLater();
        break;
    }
    case SocketEvent::InnerSocketSendEvent: {
        auto e = static_cast<SocketEvent *>(event);
        d->socket->receivedMsg(e->data());
        break;
    }
    case SocketEvent::InnerSocketCloseEvent:
        d->socket->closed();
        this->deleteLater();
        break;
    default:
        break;
    }
}
