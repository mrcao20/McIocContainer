#pragma once

#include "IMcConfigurableBeanFactory.h"

MC_INTERFACE IMcApplicationContext
	: public IMcConfigurableBeanFactory{

public:
	virtual ~IMcApplicationContext() = default;


};

