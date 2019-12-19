#ifndef IREFERENCEBEAN_H
#define IREFERENCEBEAN_H

#include <qmetaobject.h>

class IReferenceBean {

public:
    virtual ~IReferenceBean() = default;

    virtual void say() = 0;
};

Q_DECLARE_METATYPE(IReferenceBean *);

#endif // IREFERENCEBEAN_H
