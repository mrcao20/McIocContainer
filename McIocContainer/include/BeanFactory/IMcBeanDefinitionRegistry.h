/*******************************************************************
 <文件名>		IMcBeanDefinitionRegistry.h
 <详细说明>		需要一个beanDefinitionRegistry 定义关于beanDefinition的一些行为
				比如注册beanDefinition
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#pragma once

#include "../McMacroGlobal.h"

#include <qstring.h>
#include <qmap.h>
#include <QSharedPointer>

class IMcBeanDefinition;

MC_INTERFACE IMcBeanDefinitionRegistry {

public:
	virtual ~IMcBeanDefinitionRegistry() = default;

	/*************************************************
	 <函数名称>		registerBeanDefinition
	 <函数说明>		将bean的定义注册到容器中, 如果已经存在则替换
	 <参数说明>		name bean名称
					bean bean定义实例，由于bean定义可能长时间保存在工厂中，所以不要为它设置父对象，容器会自动删除
	 <返回值>
	 <作    者>		mrcao
	 <时    间>		2019/4/3
	**************************************************/
    virtual void registerBeanDefinition(const QString &name, const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT = 0;
    /*************************************************
     @Funcname  isContained
     @Brief     检测该bean是否已经存在
     @Params
     @Return    bool: true存在，false不存在
     @Author    mrcao
     @Date      2020-02-23
    **************************************************/
    virtual bool isContained(const QString &name) noexcept = 0;
	/*************************************************
	 <函数名称>		getBeanDefinitions
	 <函数说明>		获取所有bean定义
	 <参数说明>		
	 <返回值>		键为bean的名称，值为bean定义
	 <作    者>		mrcao
	 <时    间>		2019/5/6
	**************************************************/
    virtual QMap<QString, QSharedPointer<IMcBeanDefinition>> getBeanDefinitions() Q_DECL_NOEXCEPT = 0;
};
