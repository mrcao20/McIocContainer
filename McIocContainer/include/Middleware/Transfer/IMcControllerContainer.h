#pragma once

#include "../../McMacroGlobal.h"

MC_INTERFACE IMcControllerContainer {
public:
    virtual ~IMcControllerContainer() = default;
    
    virtual QVariant invoke(const QString &uri, const QVariant &body) noexcept = 0;
};

MC_DECLARE_POINTER(IMcControllerContainer)
