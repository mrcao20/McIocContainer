#pragma once

#include <QObject>

#include <QEvent>
#include <QVariant>

#include "../../../../McGlobal.h"

class SocketEvent : public QEvent {
    Q_GADGET
public:
    enum SocketEventType {
        SocketInitEvent = QEvent::Type::User + 1,
        QmlSocketErrorEvent,
        QmlSocketSendEvent,
        QmlSocketCloseEvent,
        InnerSocketErrorEvent,
        InnerSocketSendEvent,
        InnerSocketCloseEvent
    };
    Q_ENUM(SocketEventType)
    
    SocketEvent(int type, const QVariant &data);
    ~SocketEvent() override;
    
    QVariant data() const {return m_data;}
private:
    QVariant m_data;
};

MC_FORWARD_DECLARE_CLASS(McQmlSocket)
MC_FORWARD_DECLARE_CLASS(McSession)
MC_FORWARD_DECLARE_CLASS(McInnerSocket)

MC_FORWARD_DECLARE_PRIVATE_DATA(McQmlSocketRunner);

class McQmlSocketRunner : public QObject {
    Q_OBJECT
public:
    McQmlSocketRunner(QObject *parent = nullptr);
    ~McQmlSocketRunner() override;

    void setSocket(McQmlSocket *socket) noexcept;
    void setSession(const QSharedPointer<McSession> &session) noexcept;
    void setInnerSocket(const QSharedPointer<McInnerSocket> &innerSocket) noexcept;
    
    void run() noexcept;
    
protected:
    void customEvent(QEvent *event) override;

private:
    MC_DECLARE_PRIVATE(McQmlSocketRunner)
};
