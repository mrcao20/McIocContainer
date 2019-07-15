/*******************************************************************
 <文件名>		IMcBeanDefinitionReader.h
 <详细说明>		接口，定义beanDefinition的读取功能
 <作   者>		mrcao
 <日   期>		2019/4/6
********************************************************************/

#ifndef _I_MC_BEAN_DEFINITION_READER_H_
#define _I_MC_BEAN_DEFINITION_READER_H_

#include "McMacroGlobal.h"

class IMcBeanDefinitionRegistry;

MC_INTERFACE IMcBeanDefinitionReader {

public:
	virtual ~IMcBeanDefinitionReader() = default;

	/*************************************************
	 <函数名称>		readBeanDefinition
	 <函数说明>		读取beanDefinition，并将其注册进工厂。
	 <参数说明>		registry beanDefinition的注册器，将读出的beanDefinition注册进工厂中
	 <返回值>		
	 <作    者>		mrcao
	 <时    间>		2019/4/6
	**************************************************/
	virtual void readBeanDefinition(IMcBeanDefinitionRegistry *registry) Q_DECL_NOEXCEPT = 0;
};

#endif // !_I_MC_BEAN_DEFINITION_READER_H_

