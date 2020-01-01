/*******************************************************************
 @Filename  IMcApplicationContext
 @Brief
 @Author    mrcao
 @Date      2019-12-31
********************************************************************/
#pragma once

#include "../BeanFactory/IMcConfigurableBeanFactory.h"

MC_INTERFACE IMcApplicationContext
    : public IMcConfigurableBeanFactory {

public:
	virtual ~IMcApplicationContext() = default;
};

