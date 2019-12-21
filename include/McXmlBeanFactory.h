/*******************************************************************
 <�ļ���>		McXmlBeanFactory.h
 <��ϸ˵��>		ʵ��XML��ʽע��bean
 <��   ��>		mrcao
 <��   ��>		2019/4/5
********************************************************************/

#pragma once

#include "McDefaultBeanFactory.h"

class IMcBeanDefinitionReader;

struct McXmlBeanFactoryData;

class MCIOCCONTAINER_EXPORT McXmlBeanFactory : public McDefaultBeanFactory {
    Q_OBJECT

public:
	/*	���캯��������һ��reader��������read����ע��bean
		����������ʱ���Զ�����reader��������ΪΪreaderָ��������
	*/
    explicit McXmlBeanFactory(IMcBeanDefinitionReader *reader, QObject *parent = nullptr);
	virtual ~McXmlBeanFactory();

private:
	QScopedPointer<McXmlBeanFactoryData> d;
};
