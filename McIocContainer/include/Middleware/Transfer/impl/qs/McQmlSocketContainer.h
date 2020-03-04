#pragma once

#include <QObject>

#include "../../IMcQmlSocketContainer.h"

MC_FORWARD_DECLARE_CLASS(McIocBoot)
MC_FORWARD_DECLARE_CLASS(McInnerSocket)

MC_FORWARD_DECLARE_PRIVATE_DATA(McQmlSocketContainer)

class McQmlSocketContainer : public QObject, public IMcQmlSocketContainer {
    Q_OBJECT
public:
    McQmlSocketContainer(QObject *parent = nullptr);
    ~McQmlSocketContainer() override;
    
    void init(const QSharedPointer<McIocBoot> &boot) noexcept;
    
    McQmlSocket *addConnect(const QString &uri) noexcept override;
    McQmlSocket *addConnect(const QString &uri, const QJSValue &data) noexcept override;
    
private:
    void addConnect(McQmlSocket *socket, const QString &uri) noexcept;
    QSharedPointer<McInnerSocket> getMethods(const QSharedPointer<QObject> &bean) noexcept;
    
private:
    MC_DECLARE_PRIVATE(McQmlSocketContainer)
};

MC_DECLARE_POINTER(McQmlSocketContainer)
