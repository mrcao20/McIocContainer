#pragma once

#include <qmetaobject.h>
#include "ApplicationContext/McContainerGlobal.h"

class IHelloWorld {
    Q_GADGET
    Q_CLASSINFO("ss", "aa")
    MC_DEFINE_TYPELIST()
public:
	virtual ~IHelloWorld() = default;

	virtual void say() = 0;
};

MC_DECLARE_METATYPE(IHelloWorld)
