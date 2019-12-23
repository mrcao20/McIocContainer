#pragma once

#include <qmetaobject.h>
#include "McBeanGlobal.h"

class IHelloWorld {

public:
	virtual ~IHelloWorld() = default;

	virtual void say() = 0;
};

MC_DECLARE_METATYPE(IHelloWorld)
