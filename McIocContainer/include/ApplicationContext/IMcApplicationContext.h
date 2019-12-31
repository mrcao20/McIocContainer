/*******************************************************************
 @Filename  IMcApplicationContext
 @Brief     注意: 为了避免直接将this指针传递给BeanDefinitionReader，所以此处不继承IMcBeanDefinitionRegistry
 @Author    mrcao
 @Date      2019-12-31
********************************************************************/
#pragma once

#include "../BeanFactory/IMcBeanFactory.h"

MC_INTERFACE IMcApplicationContext
    : public IMcBeanFactory{

public:
	virtual ~IMcApplicationContext() = default;
};

