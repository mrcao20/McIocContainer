#include "include/Middleware/Transfer/impl/qs/McSession.h"

#include <QQmlEngine>
#include <QJsonObject>

MC_STATIC(McSession)
mcRegisterBeanFactory<McSession>("McSession");
MC_STATIC_END();

McSession::McSession(QObject *parent)
    : QObject(parent)
{
}

McSession::~McSession() {
    close();
}

void McSession::send(const QString &msg) noexcept {
    emit signal_send(msg);
}

void McSession::send(const QJsonObject &jsonObj) noexcept {
    emit signal_send(jsonObj);
}

void McSession::send(QObject *obj) noexcept {
    QQmlEngine::setObjectOwnership(obj, QQmlEngine::JavaScriptOwnership);
    QVariant var;
    var.setValue(obj);
    emit signal_send(var);
}
