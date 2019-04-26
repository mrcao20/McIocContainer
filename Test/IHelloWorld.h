#pragma once

#include <qmetaobject.h>

class IHelloWorld {

public:
	virtual ~IHelloWorld() = default;

	virtual void say() = 0;
};

Q_DECLARE_METATYPE(IHelloWorld *);