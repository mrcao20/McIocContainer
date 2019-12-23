#pragma once

#include "IReferenceBean.h"

class IRR : public IReferenceBean {
    MC_DEFINE_TYPELIST(MC_TYPELIST(IReferenceBean))
public:
    ~IRR() override = default;
};

MC_DECLARE_METATYPE(IRR)
