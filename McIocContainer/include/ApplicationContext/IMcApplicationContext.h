#pragma once

#include "../BeanFactory/IMcConfigurableBeanFactory.h"

MC_INTERFACE IMcApplicationContext
	: public IMcConfigurableBeanFactory{

public:
	virtual ~IMcApplicationContext() = default;
};

