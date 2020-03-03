#pragma once

#include "../McMacroGlobal.h"

MC_INTERFACE IMcReadableApplicationContext {
public:
    virtual ~IMcReadableApplicationContext() = default;
    
    virtual void readBeans() noexcept = 0;
};
