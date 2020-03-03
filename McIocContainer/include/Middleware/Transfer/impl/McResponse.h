#pragma once

#include <QObject>

#include "include/McMacroGlobal.h"
#include "include/ApplicationContext/McContainerGlobal.h"

MC_FORWARD_DECLARE_CLASS(QJSValue)

MC_FORWARD_DECLARE_PRIVATE_DATA(McResponse)

class McResponse : public QObject {
    Q_OBJECT
    MC_DECL_STATIC(McResponse)
public:
    explicit McResponse(QObject *parent = nullptr);
    ~McResponse() override;
    
    void setBody(const QVariant &var) noexcept;

    Q_INVOKABLE McResponse *then(const QJSValue &callback) noexcept;
    Q_INVOKABLE McResponse *syncThen(const QJSValue &callback) noexcept;
    
protected:
    void customEvent(QEvent *event) override;
    
private:
    void callCallback() noexcept;

private:
    MC_DECLARE_PRIVATE(McResponse)
};

Q_DECLARE_METATYPE(McResponse *)
    
