/*******************************************************************
 @Filename  IMcApplicationContext
 @Brief
 @Author    mrcao
 @Date      2019-12-31
********************************************************************/
#pragma once

#include "../BeanFactory/IMcConfigurableBeanFactory.h"
#include "../ApplicationContext/IMcRefreshableApplicationContext.h"

MC_INTERFACE IMcApplicationContext
    : public IMcConfigurableBeanFactory
    , public IMcRefreshableApplicationContext {

public:
	virtual ~IMcApplicationContext() = default;
};

