/*******************************************************************
 <�ļ���>		IMcBeanDefinitionRegistry.h
 <��ϸ˵��>		��Ҫһ��beanDefinitionRegistry �������beanDefinition��һЩ��Ϊ
				����ע��beanDefinition
 <��   ��>		mrcao
 <��   ��>		2019/4/3
********************************************************************/

#pragma once

#include "McMacroGlobal.h"

#include <qstring.h>
#include <qmap.h>
#include <QSharedPointer>

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
    virtual void registerBeanDefinition(const QString &name, const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT = 0;
	/*************************************************
	 <��������>		getBeanDefinitions
	 <����˵��>		��ȡ����bean����
	 <����˵��>		
	 <����ֵ>		��Ϊbean�����ƣ�ֵΪbean����
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/5/6
	**************************************************/
    virtual QMap<QString, QSharedPointer<IMcBeanDefinition>> getBeanDefinitions() Q_DECL_NOEXCEPT = 0;
};
