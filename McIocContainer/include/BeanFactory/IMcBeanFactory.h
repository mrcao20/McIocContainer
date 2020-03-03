/*******************************************************************
 <文件名>		IMcBeanFactory.h
 <详细说明>		需要一个beanFactory 定义ioc 容器的一些行为 
				比如根据名称获取bean， 
				比如注册bean，参数为bean的名称，bean的定义。
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#pragma once

#include "../McMacroGlobal.h"

#include <QObject>
#include <QVariant>

MC_INTERFACE IMcBeanFactory {

public:
	virtual ~IMcBeanFactory() = default;

	/*************************************************
	 <函数名称>		getBean
	 <函数说明>		根据bean的名称从容器中获取bean对象，此函数是线程安全的。
	 <参数说明>		name bean名称
     <返回值>        bean实例。
                    注意：此函数可能返回空
	 <作    者>		mrcao
     <时    间>		2019/12/22
	**************************************************/
    virtual QSharedPointer<QObject> getBean(const QString &name) Q_DECL_NOEXCEPT = 0;
    /*************************************************
     <函数名称>		getBeanToVariant
     <函数说明>		根据bean的名称从容器中获取bean对象，此函数是线程安全的。
     <参数说明>		name bean名称
     <返回值>        包含bean实例的QVariant。
                    注意：此函数可能返回无效的QVariant
     <作    者>		mrcao
     <时    间>		2019/12/22
    **************************************************/
    virtual QVariant getBeanToVariant(const QString &name)  Q_DECL_NOEXCEPT = 0;
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
