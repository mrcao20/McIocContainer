/*******************************************************************
 <文件名>		IMcBeanReferenceResolver.h
 <详细说明>		需要一个beanReferenceResolver 定义关于beanReference的一些行为 
				比如根据beanReference生成实例对象
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#pragma once

#include "../McMacroGlobal.h"

#include <qobject.h>

class McBeanReference;

MC_INTERFACE IMcBeanReferenceResolver {

public:
	virtual ~IMcBeanReferenceResolver() = default;

	/*************************************************
	 <函数名称>		resolveBeanReference
	 <函数说明>		根据beanReference生成实例对象。
	 <参数说明>		beanRef beanReference
     <返回值>        生成的reference实例
	 <作    者>		mrcao
	 <时    间>		2019/4/3
	**************************************************/
    virtual QSharedPointer<QObject> resolveBeanReference(const QSharedPointer<McBeanReference>& beanRef) Q_DECL_NOEXCEPT = 0;
    /*************************************************
     <函数名称>		resolveBeanReferenceToQVariant
     <函数说明>		根据beanReference生成包含实例对象的QVariant。
     <参数说明>		beanRef beanReference
     <返回值>        生成包含reference实例的QVariant
                    注：QVariant中包含的类型为QSharedPointer<McBeanReference::getName()>，即最底层类型
     <作    者>		mrcao
     <时    间>		2019/12/22
    **************************************************/
    virtual QVariant resolveBeanReferenceToQVariant(const QSharedPointer<McBeanReference>& beanRef) Q_DECL_NOEXCEPT = 0;
};
