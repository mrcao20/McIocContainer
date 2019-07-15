/*******************************************************************
 <文件名>		IMcBeanReferenceResolver.h
 <详细说明>		需要一个beanReferenceResolver 定义关于beanReference的一些行为 
				比如根据beanReference生成实例对象
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#ifndef _I_MC_BEAN_REFERENCE_RESOLVER_H_
#define _I_MC_BEAN_REFERENCE_RESOLVER_H_

#include "McMacroGlobal.h"

#include <qobject.h>

class McBeanReference;

MC_INTERFACE IMcBeanReferenceResolver {

public:
	virtual ~IMcBeanReferenceResolver() = default;

	/*************************************************
	 <函数名称>		resolveBeanReference
	 <函数说明>		根据beanReference生成实例对象。
	 <参数说明>		beanRef beanReference
	 <返回值>		生成的reference实例
	 <作    者>		mrcao
	 <时    间>		2019/4/3
	**************************************************/
	virtual QObject *resolveBeanReference(McBeanReference *beanRef) Q_DECL_NOEXCEPT = 0;
};

#endif // !_I_MC_BEAN_REFERENCE_RESOLVER_H_