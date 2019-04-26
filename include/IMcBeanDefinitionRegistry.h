/*******************************************************************
 <�ļ���>		IMcBeanDefinitionRegistry.h
 <��ϸ˵��>		��Ҫһ��beanDefinitionRegistry �������beanDefinition��һЩ��Ϊ
				����ע��beanDefinition
 <��   ��>		mrcao
 <��   ��>		2019/4/3
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
	 <��������>		registerBeanDefinition
	 <����˵��>		��bean�Ķ���ע�ᵽ������.
	 <����˵��>		name bean����
					bean bean����ʵ��������bean������ܳ�ʱ�䱣���ڹ����У����Բ�ҪΪ�����ø������������Զ�ɾ��
	 <����ֵ>
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
	virtual void registerBeanDefinition(const QString &name, IMcBeanDefinition *bean) Q_DECL_NOEXCEPT = 0;
};

#endif // !_I_MC_BEAN_DEFINITION_REGISTRY_H_