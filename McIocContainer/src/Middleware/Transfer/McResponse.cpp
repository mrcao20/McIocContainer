#include "include/Middleware/Transfer/impl/McResponse.h"

#include <QVariant>
#include <QJSValue>
#include <QJSEngine>
#include <QEvent>
#include <QCoreApplication>

MC_DECLARE_PRIVATE_DATA(McResponse)
MC_PADDING_CLANG(7)
bool isSyncCall{false};         // 是否让线程回到主线程再执行callback，默认不需要
QJSValue callback;
QVariant body;
MC_DECLARE_PRIVATE_DATA_END();

MC_STATIC(McResponse)
qRegisterMetaType<McResponse *>("McResponse");
MC_STATIC_END()

McResponse::McResponse(QObject *parent)
    : QObject(parent)
    , MC_NEW_PRIVATE_DATA(McResponse)
{
}

McResponse::~McResponse() {
}

void McResponse::setBody(const QVariant &var) noexcept {
    MC_D(McResponse);
    d->body = var;
    
    if(d->isSyncCall) {
        // 发布的事件由QT删除
        qApp->postEvent(this, new QEvent(static_cast<QEvent::Type>(QEvent::Type::User + 1)));
        return;
    }
    
    callCallback();
}

McResponse *McResponse::then(const QJSValue &callback) noexcept {
    MC_D(McResponse);
    d->callback = callback;
    d->isSyncCall = false;
    return this;
}

McResponse *McResponse::syncThen(const QJSValue &callback) noexcept {
    MC_D(McResponse);
    d->callback = callback;
    d->isSyncCall = true;
    return this;
}

void McResponse::customEvent(QEvent *event) {
    if(event->type() == QEvent::Type::User + 1) {
        callCallback();
    }
}

void McResponse::callCallback() noexcept {
    MC_D(McResponse);
    auto engine = qjsEngine(this);
    if(!engine) {
        return;
    }
    auto arg = engine->toScriptValue(d->body);
    d->callback.call(QJSValueList() << arg);
}
