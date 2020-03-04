#pragma once

#include <QObject>

#include "../../../../McMacroGlobal.h"

MC_FORWARD_DECLARE_PRIVATE_DATA(McInnerSocket)
MC_FORWARD_DECLARE_CLASS(McSession)

class McInnerSocket : public QObject {
    Q_OBJECT
public:
    explicit McInnerSocket(QObject *parent = nullptr);
    ~McInnerSocket() override;

    void setInnerSocketObj(const QSharedPointer<QObject> &obj) noexcept;
    
    void setOnOpen(const QMetaMethod &method) noexcept;
    void setOnClose(const QMetaMethod &method) noexcept;
    void setOnError(const QMetaMethod &method) noexcept;
    void setOnMessage(const QMetaMethod &method) noexcept;
    
    void opened(const QSharedPointer<McSession> &session) noexcept;
    void closed(const QSharedPointer<McSession> &session) noexcept;
    void errored(const QSharedPointer<McSession> &session, const QString &errMsg) noexcept;
    void receivedMsg(const QSharedPointer<McSession> &session, const QVariant &msg) noexcept;
    
private:
    void invoke(const QMetaMethod &method
                , const QVector<QGenericArgument> &args) noexcept;
    
private:
    MC_DECLARE_PRIVATE(McInnerSocket)
};

MC_DECLARE_POINTER(McInnerSocket)
