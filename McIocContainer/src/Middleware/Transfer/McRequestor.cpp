#include "include/Middleware/Transfer/impl/McRequestor.h"

#include <QThreadPool>
#include <QQmlEngine>

#include "include/Middleware/Transfer/IMcControllerContainer.h"
#include "include/Middleware/Transfer/IMcQmlSocketContainer.h"
#include "include/Middleware/Transfer/impl/McResponse.h"
#include "include/Middleware/Transfer/impl/McRequestRunner.h"
#include "include/Middleware/Transfer/impl/qs/McQmlSocket.h"

MC_DECLARE_PRIVATE_DATA(McRequestor)
QSharedPointer<QThreadPool> threadPool;
IMcControllerContainerPtr controllerContainer;
IMcQmlSocketContainerPtr qmlSocketContainer;
MC_DECLARE_PRIVATE_DATA_END()

McRequestor::McRequestor(QObject *parent)
    : QObject(parent)
    , MC_NEW_PRIVATE_DATA(McRequestor)
{
    MC_D(McRequestor);
    d->threadPool = QSharedPointer<QThreadPool>::create();
    
    setMaxThreadCount(100);     // 默认线程数量
}

McRequestor::~McRequestor() {
}

qint64 McRequestor::maxThreadCount() const noexcept {
    MC_D(McRequestor);
    return d->threadPool->maxThreadCount();
}

void McRequestor::setMaxThreadCount(int val) noexcept {
    MC_D(McRequestor);
    d->threadPool->setMaxThreadCount(val);
}

void McRequestor::setControllerContainer(const IMcControllerContainerPtr &val) noexcept {
    MC_D(McRequestor);
    d->controllerContainer = val;
}

void McRequestor::setSocketContainer(const QSharedPointer<IMcQmlSocketContainer> &val) noexcept {
    MC_D(McRequestor);
    d->qmlSocketContainer = val;
}

McResponse *McRequestor::invoke(const QString &uri) noexcept {
    auto response = newResponse();
    run(response, uri, QVariant());
    return response;    // 没有指定父对象，该对象的所有权将归QML所有
}

McResponse *McRequestor::invoke(const QString &uri, const QJsonObject &data) noexcept {
    auto response = newResponse();
    run(response, uri, data);
    return response;    // 没有指定父对象，该对象的所有权将归QML所有
}

McQmlSocket *McRequestor::addConnect(const QString &uri) noexcept {
    MC_D(McRequestor);
    auto qs = d->qmlSocketContainer->addConnect(uri);
    QQmlEngine::setObjectOwnership(qs, QQmlEngine::JavaScriptOwnership);
    return qs;
}

McQmlSocket *McRequestor::addConnect(const QString &uri, const QJSValue &data) noexcept {
    MC_D(McRequestor);
    auto qs = d->qmlSocketContainer->addConnect(uri, data);
    QQmlEngine::setObjectOwnership(qs, QQmlEngine::JavaScriptOwnership);
    return qs;
}

McResponse *McRequestor::newResponse() noexcept {
    McResponse *response = new McResponse();
    QQmlEngine::setObjectOwnership(response, QQmlEngine::JavaScriptOwnership);
    return response;
}

void McRequestor::run(McResponse *response, const QString &uri, const QVariant &body) noexcept {
    MC_D(McRequestor);
    McRequestRunner *runner = new McRequestRunner();
    runner->setAutoDelete(true);
    runner->setResponse(response);
    runner->setControllerContainer(d->controllerContainer);
    runner->setUri(uri);
    runner->setBody(body);
    d->threadPool->start(runner);
}
