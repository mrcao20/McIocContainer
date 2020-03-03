#pragma once

#include "../../McMacroGlobal.h"

QT_BEGIN_NAMESPACE
MC_FORWARD_DECLARE_CLASS(QJSValue)
QT_END_NAMESPACE

MC_FORWARD_DECLARE_CLASS(McQmlSocket)

MC_INTERFACE IMcQmlSocketContainer {
public:
    virtual ~IMcQmlSocketContainer() = default;
    
    virtual McQmlSocket *addConnect(const QString &uri) noexcept = 0;
    virtual McQmlSocket *addConnect(const QString &uri, const QJSValue &data) noexcept = 0;
};

MC_DECLARE_POINTER(IMcQmlSocketContainer)
