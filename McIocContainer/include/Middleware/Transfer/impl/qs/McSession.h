#pragma once

#include <QObject>

#include <QVariant>

#include "../../../../McMacroGlobal.h"
#include "../../../../ApplicationContext/McContainerGlobal.h"

QT_BEGIN_NAMESPACE
MC_FORWARD_DECLARE_CLASS(QJsonObject)
QT_END_NAMESPACE

class MCIOCCONTAINER_EXPORT McSession : public QObject {
    Q_OBJECT
    MC_DECL_STATIC(McSession)
public:
    explicit McSession(QObject *parent = nullptr);
    ~McSession() override;
    
    void send(const QString &msg) noexcept;
    void send(const QJsonObject &jsonObj) noexcept;
    void send(QObject *obj) noexcept;
    
signals:
    void signal_send(const QVariant &);
    void close();
};
    
MC_DECLARE_METATYPE(McSession)
