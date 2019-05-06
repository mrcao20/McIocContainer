/*******************************************************************
 <文件名>		IMcBeanFactory.h
 <详细说明>		需要一个beanFactory 定义ioc 容器的一些行为 
				比如根据名称获取bean， 
				比如注册bean，参数为bean的名称，bean的定义。
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#ifndef _I_MC_BEAN_FACTORY_H_
#define _I_MC_BEAN_FACTORY_H_

#include "McMacroGlobal.h"

#include <qobject.h>

MC_INTERFACE IMcBeanFactory {

public:
	virtual ~IMcBeanFactory() = default;

	/*************************************************
	 <函数名称>		getBean
	 <函数说明>		根据bean的名称从容器中获取bean对象，此函数是线程安全的。
	 <参数说明>		name bean名称
	 <返回值>		bean实例。注意：由于工厂随时都可能被销毁，为防止实例化出的bean失效，
					该bean未设置父对象，故需手动delete；也可以指定第二个参数设置bean的父对象
					注意：此函数可能返回null
	 <作    者>		mrcao
	 <时    间>		2019/4/3
	**************************************************/
	virtual QObject *getBean(const QString &name, QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT = 0;
	/*************************************************
	 <函数名称>		containsBean
	 <函数说明>		检测容器中是否存在该bean
	 <参数说明>		name bean名称
	 <返回值>		true存在，false不存在
	 <作    者>		mrcao
	 <时    间>		2019/4/3
	**************************************************/
	virtual bool containsBean(const QString &name) Q_DECL_NOEXCEPT = 0;
};

#endif // !_I_MC_BEAN_FACTORY_H_

