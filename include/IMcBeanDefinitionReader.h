/*******************************************************************
 <�ļ���>		IMcBeanDefinitionReader.h
 <��ϸ˵��>		�ӿڣ�����beanDefinition�Ķ�ȡ����
 <��   ��>		mrcao
 <��   ��>		2019/4/6
********************************************************************/

#ifndef _I_MC_BEAN_DEFINITION_READER_H_
#define _I_MC_BEAN_DEFINITION_READER_H_

#include "McMacroGlobal.h"

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
	virtual void readBeanDefinition(IMcBeanDefinitionRegistry *registry) Q_DECL_NOEXCEPT = 0;
};

#endif // !_I_MC_BEAN_DEFINITION_READER_H_

