#include "QmlSocketTest.h"

#include <QtDebug>
#include <QJsonObject>
#include <Middleware/Transfer/impl/qs/McSession.h>

MC_STATIC(QmlSocketTest)
mcRegisterComponent<QmlSocketTest>("QmlSocketTest");
MC_STATIC_END()

QmlSocketTest::QmlSocketTest(QObject *parent)
    : QObject(parent)
{
}

QmlSocketTest::~QmlSocketTest(){}

void QmlSocketTest::onOpen(const QSharedPointer<McSession> &session) noexcept {
    qDebug() << "onOpen" << session;
}

void QmlSocketTest::onClose(const QSharedPointer<McSession> &session) noexcept {
    qDebug() << "onClose" << session;
}

void QmlSocketTest::onError(const QSharedPointer<McSession> &session) noexcept {
    qDebug() << "onError" << session;
}

void QmlSocketTest::onMessage(const QSharedPointer<McSession> &session, const QString &msg) noexcept {
    qDebug() << "onMessage" << session << msg;
    auto o = QJsonObject({{"a", "b"}});
    session->send(o);
}
