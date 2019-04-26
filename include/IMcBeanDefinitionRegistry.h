/*******************************************************************
 <文件名>		IMcBeanDefinitionRegistry.h
 <详细说明>		需要一个beanDefinitionRegistry 定义关于beanDefinition的一些行为
				比如注册beanDefinition
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#ifndef _I_MC_BEAN_DEFINITION_REGISTRY_H_
#define _I_MC_BEAN_DEFINITION_REGISTRY_H_

#include "McMacroGlobal.h"

#include <qstring.h>

class IMcBeanDefinition;

MC_INTERFACE IMcBeanDefinitionRegistry {

public:
	virtual ~IMcBeanDefinitionRegistry() = default;

	/*************************************************
	 <函数名称>		registerBeanDefinition
	 <函数说明>		将bean的定义注册到容器中.
	 <参数说明>		name bean名称
					bean bean定义实例，由于bean定义可能长时间保存在工厂中，所以不要为它设置父对象，容器会自动删除
	 <返回值>
	 <作    者>		mrcao
	 <时    间>		2019/4/3
	**************************************************/
	virtual void registerBeanDefinition(const QString &name, IMcBeanDefinition *bean) Q_DECL_NOEXCEPT = 0;
};

#endif // !_I_MC_BEAN_DEFINITION_REGISTRY_H_