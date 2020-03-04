#pragma once

#include <QObject>

#include <QJsonObject>

#include "include/McMacroGlobal.h"

QT_BEGIN_NAMESPACE
MC_FORWARD_DECLARE_CLASS(QRunable)
MC_FORWARD_DECLARE_CLASS(QJSValue)
QT_END_NAMESPACE

MC_FORWARD_DECLARE_PRIVATE_DATA(McRequestor)

MC_FORWARD_DECLARE_CLASS(IMcControllerContainer)
MC_FORWARD_DECLARE_CLASS(IMcQmlSocketContainer)
MC_FORWARD_DECLARE_CLASS(McResponse)
MC_FORWARD_DECLARE_CLASS(McRequestRunner)
MC_FORWARD_DECLARE_CLASS(McQmlSocket)

class McRequestor : public QObject {
    Q_OBJECT
public:
    explicit McRequestor(QObject *parent = nullptr);
    ~McRequestor() override;

    qint64 maxThreadCount() const noexcept;
    void setMaxThreadCount(int val) noexcept;
    void setControllerContainer(const QSharedPointer<IMcControllerContainer> &val) noexcept;
    void setSocketContainer(const QSharedPointer<IMcQmlSocketContainer> &val) noexcept;
    
    Q_INVOKABLE McResponse *invoke(const QString &uri) noexcept;
	Q_INVOKABLE McResponse *invoke(const QString &uri, const QJsonObject &data) noexcept;
    Q_INVOKABLE McQmlSocket *addConnect(const QString &uri) noexcept;
    Q_INVOKABLE McQmlSocket *addConnect(const QString &uri, const QJSValue &data) noexcept;
    
private:
    McResponse *newResponse() noexcept;
    void run(McResponse *response, const QString &uri, const QVariant &body) noexcept;
    
private:
    MC_DECLARE_PRIVATE(McRequestor)
};

MC_DECLARE_POINTER(McRequestor)
