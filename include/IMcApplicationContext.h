#ifndef _I_MC_APPLICATION_CONTEXT_H_
#define _I_MC_APPLICATION_CONTEXT_H_

#include "IMcConfigurableBeanFactory.h"

MC_INTERFACE IMcApplicationContext
	: public IMcConfigurableBeanFactory{

public:
	virtual ~IMcApplicationContext() = default;


};

#endif // !_I_MC_APPLICATION_CONTEXT_H_

