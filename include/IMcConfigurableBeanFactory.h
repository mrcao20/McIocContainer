/*******************************************************************
 <�ļ���>		IMcConfigurableBeanFactory.h
 <��ϸ˵��>		�ӿڣ��ṩbean�Ļ�ȡ��beanDefinition��ע��ȹ���
 <��   ��>		mrcao
 <��   ��>		2019/4/7
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

