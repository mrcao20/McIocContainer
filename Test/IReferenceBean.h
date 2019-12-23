#ifndef IREFERENCEBEAN_H
#define IREFERENCEBEAN_H

#include <qmetaobject.h>

#include "McBeanGlobal.h"

class IReferenceBean {
    MC_DEFINE_TYPELIST()
public:
    virtual ~IReferenceBean() = default;

    virtual void say() = 0;
};

MC_DECLARE_METATYPE(IReferenceBean)

#endif // IREFERENCEBEAN_H
