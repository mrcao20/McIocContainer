#include "include/Middleware/Transfer/impl/McRequestRunner.h"

#include <QVariant>
#include <QPointer>

#include "include/Middleware/Transfer/impl/McResponse.h"
#include "include/Middleware/Transfer/IMcControllerContainer.h"

MC_DECLARE_PRIVATE_DATA(McRequestRunner)
QPointer<McResponse> response;
IMcControllerContainerPtr controllerContainer;
QString uri;
QVariant body;
MC_DECLARE_PRIVATE_DATA_END()

McRequestRunner::McRequestRunner()
    : MC_NEW_PRIVATE_DATA(McRequestRunner)
{
}

McRequestRunner::~McRequestRunner() {
}

void McRequestRunner::setResponse(McResponse *val) noexcept {
    MC_D(McRequestRunner);
    d->response = val;
}

void McRequestRunner::setControllerContainer(const IMcControllerContainerPtr &val) noexcept {
    MC_D(McRequestRunner);
    d->controllerContainer = val;
}

void McRequestRunner::setUri(const QString &uri) noexcept {
    MC_D(McRequestRunner);
    d->uri = uri;
}

void McRequestRunner::setBody(const QVariant &body) noexcept {
    MC_D(McRequestRunner);
    d->body = body;
}

void McRequestRunner::run() {
    MC_D(McRequestRunner);
    auto body = d->controllerContainer->invoke(d->uri, d->body);
    Q_ASSERT(!d->response.isNull());
    d->response->setBody(body);
}
