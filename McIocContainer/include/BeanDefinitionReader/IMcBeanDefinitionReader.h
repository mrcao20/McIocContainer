/*******************************************************************
 <�ļ���>		IMcBeanDefinitionReader.h
 <��ϸ˵��>		�ӿڣ�����beanDefinition�Ķ�ȡ����
 <��   ��>		mrcao
 <��   ��>		2019/4/6
********************************************************************/

#pragma once

#include "../McMacroGlobal.h"

#include <QSharedPointer>

class IMcBeanDefinitionRegistry;

MC_INTERFACE IMcBeanDefinitionReader {

public:
	virtual ~IMcBeanDefinitionReader() = default;

	/*************************************************
	 <��������>		readBeanDefinition
	 <����˵��>		��ȡbeanDefinition��������ע���������
	 <����˵��>		registry beanDefinition��ע��������������beanDefinitionע���������
	 <����ֵ>		
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/6
	**************************************************/
    virtual void readBeanDefinition(const QSharedPointer<IMcBeanDefinitionRegistry>& registry) Q_DECL_NOEXCEPT = 0;
};
