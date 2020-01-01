/*******************************************************************
 <文件名>		IMcConfigurableBeanFactory.h
 <详细说明>		接口，提供bean的获取和beanDefinition的注册等功能
 <作   者>		mrcao
 <日   期>		2019/4/7
********************************************************************/

#pragma once

#include "IMcBeanFactory.h"
#include "IMcBeanDefinitionRegistry.h"

MC_INTERFACE IMcConfigurableBeanFactory
	: public IMcBeanFactory
	, public IMcBeanDefinitionRegistry {
	
public:
	virtual ~IMcConfigurableBeanFactory() = default;
};

MC_DECLARE_POINTER(IMcConfigurableBeanFactory)
