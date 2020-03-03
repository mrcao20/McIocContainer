#include "include/Middleware/Transfer/impl/qs/McInnerSocket.h"

#include <QMetaMethod>
#include <QVector>

MC_DECLARE_PRIVATE_DATA(McInnerSocket)
QSharedPointer<QObject> innerSocketObj;
QMetaMethod onOpen;
QMetaMethod onClose;
QMetaMethod onError;
QMetaMethod onMessage;
MC_DECLARE_PRIVATE_DATA_END()

McInnerSocket::McInnerSocket(QObject *parent)
    : QObject(parent)
    , MC_NEW_PRIVATE_DATA(McInnerSocket)
{
}

McInnerSocket::~McInnerSocket() {
}

void McInnerSocket::setInnerSocketObj(const QSharedPointer<QObject> &obj) noexcept {
    MC_D(McInnerSocket);
    d->innerSocketObj = obj;
}

void McInnerSocket::setOnOpen(const QMetaMethod &method) noexcept {
    MC_D(McInnerSocket);
    d->onOpen = method;
}

void McInnerSocket::setOnClose(const QMetaMethod &method) noexcept {
    MC_D(McInnerSocket);
    d->onClose = method;
}

void McInnerSocket::setOnError(const QMetaMethod &method) noexcept {
    MC_D(McInnerSocket);
    d->onError = method;
}

void McInnerSocket::setOnMessage(const QMetaMethod &method) noexcept {
    MC_D(McInnerSocket);
    d->onMessage = method;
}

void McInnerSocket::opened(const QSharedPointer<McSession> &session) noexcept {
    MC_D(McInnerSocket);
    auto method = d->onOpen;
    
    if(!method.isValid()) {
        return;
    }
    
    QVector<QGenericArgument> arguments;
	arguments.resize(10);
    
    int sessionTypeId = QMetaType::type(MC_MACRO_STR(QSharedPointer<McSession>));
    for(int i = 0; i < method.parameterCount(); ++i) {
        if(i >= 10) {
            break;
        }
        auto id = method.parameterType(i);
        if(id == sessionTypeId) {
            arguments.replace(i, Q_ARG(QSharedPointer<McSession>, session));
            break;
        }
    }
    
    invoke(method, arguments);
}

void McInnerSocket::closed(const QSharedPointer<McSession> &session) noexcept {
    MC_D(McInnerSocket);
    auto method = d->onClose;
    
    if(!method.isValid()) {
        return;
    }
    
    QVector<QGenericArgument> arguments;
	arguments.resize(10);
    
    int sessionTypeId = QMetaType::type(MC_MACRO_STR(QSharedPointer<McSession>));
    for(int i = 0; i < method.parameterCount(); ++i) {
        if(i >= 10) {
            break;
        }
        auto id = method.parameterType(i);
        if(id == sessionTypeId) {
            arguments.replace(i, Q_ARG(QSharedPointer<McSession>, session));
            break;
        }
    }
    
    invoke(method, arguments);
}

void McInnerSocket::errored(const QSharedPointer<McSession> &session, const QString &errMsg) noexcept {
    MC_D(McInnerSocket);
    auto method = d->onError;
    
    if(!method.isValid()) {
        return;
    }
    
    QVector<QGenericArgument> arguments;
	arguments.resize(10);
    
    int sessionTypeId = QMetaType::type(MC_MACRO_STR(QSharedPointer<McSession>));
    int stringTypeId = QMetaType::type(MC_MACRO_STR(QString));
    for(int i = 0; i < method.parameterCount(); ++i) {
        if(i >= 10) {
            break;
        }
        auto id = method.parameterType(i);
        if(id == sessionTypeId) {
            arguments.replace(i, Q_ARG(QSharedPointer<McSession>, session));
        }else if(id == stringTypeId) {
            arguments.replace(i, Q_ARG(QString, errMsg));
        }
    }
    
    invoke(method, arguments);
}

void McInnerSocket::receivedMsg(const QSharedPointer<McSession> &session, const QVariant &msg) noexcept {
    MC_D(McInnerSocket);
    auto method = d->onMessage;
    
    if(!method.isValid()) {
        return;
    }
    
    auto tempMsg = msg;
    
    QVector<QGenericArgument> arguments;
	arguments.resize(10);
    
    int sessionTypeId = QMetaType::type(MC_MACRO_STR(QSharedPointer<McSession>));
    for(int i = 0; i < method.parameterCount(); ++i) {
        if(i >= 10) {
            break;
        }
        auto id = method.parameterType(i);
        Q_ASSERT_X(id != QMetaType::Type::UnknownType
                , "InnerSocket"
                , "onMessage contained a not register type");
        if(id == sessionTypeId) {
            arguments.replace(i, Q_ARG(QSharedPointer<McSession>, session));
        }else{
            tempMsg.convert(id);
            arguments.replace(i, QGenericArgument("QVariant", tempMsg.data()));
        }
    }
    
    invoke(method, arguments);
}

void McInnerSocket::invoke(const QMetaMethod &method
                           , const QVector<QGenericArgument> &args) noexcept {
    
    MC_D(McInnerSocket);
    method.invoke(d->innerSocketObj.data(),
            Qt::DirectConnection, 
            args.at(0),
            args.at(1),
            args.at(2),
            args.at(3),
            args.at(4),
            args.at(5),
            args.at(6),
            args.at(7),
            args.at(8),
            args.at(9));
}
