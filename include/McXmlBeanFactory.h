/*******************************************************************
 <�ļ���>		McXmlBeanFactory.h
 <��ϸ˵��>		ʵ��XML��ʽע��bean
 <��   ��>		mrcao
 <��   ��>		2019/4/5
********************************************************************/

#ifndef _MC_XML_BEAN_FACTORY_H_
#define _MC_XML_BEAN_FACTORY_H_

#include "McDefaultBeanFactory.h"

class IMcBeanDefinitionReader;

struct McXmlBeanFactoryData;

class MCIOCCONTAINER_EXPORT McXmlBeanFactory : public McDefaultBeanFactory {
	Q_OBJECT;

public:
	/*	���캯��������һ��reader��������read����ע��bean
		����������ʱ���Զ�����reader��������ΪΪreaderָ��������
	*/
	explicit McXmlBeanFactory(IMcBeanDefinitionReader *reader, QObject *parent = 0);
	virtual ~McXmlBeanFactory();

private:
	QScopedPointer<McXmlBeanFactoryData> d;
};

#endif // !_MC_XML_BEAN_FACTORY_H_
