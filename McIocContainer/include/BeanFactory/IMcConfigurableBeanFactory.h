/*******************************************************************
 <�ļ���>		IMcConfigurableBeanFactory.h
 <��ϸ˵��>		�ӿڣ��ṩbean�Ļ�ȡ��beanDefinition��ע��ȹ���
 <��   ��>		mrcao
 <��   ��>		2019/4/7
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
