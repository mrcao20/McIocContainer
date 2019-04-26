/*******************************************************************
 <文件名>		IMcConfigurableBeanFactory.h
 <详细说明>		接口，提供bean的获取和beanDefinition的注册等功能
 <作   者>		mrcao
 <日   期>		2019/4/7
********************************************************************/

#ifndef _I_MC_CONFIGURABLE_BEAN_FACTORY_H_
#define _I_MC_CONFIGURABLE_BEAN_FACTORY_H_

#include "IMcBeanFactory.h"
#include "IMcBeanDefinitionRegistry.h"

MC_INTERFACE IMcConfigurableBeanFactory
	: public IMcBeanFactory
	, public IMcBeanDefinitionRegistry {
	
public:
	virtual ~IMcConfigurableBeanFactory() = default;
};

#endif // !_I_MC_CONFIGURABLE_BEAN_FACTORY_H_

