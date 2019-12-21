/*******************************************************************
 <文件名>		McXmlBeanFactory.h
 <详细说明>		实现XML方式注入bean
 <作   者>		mrcao
 <日   期>		2019/4/5
********************************************************************/

#pragma once

#include "McDefaultBeanFactory.h"

class IMcBeanDefinitionReader;

struct McXmlBeanFactoryData;

class MCIOCCONTAINER_EXPORT McXmlBeanFactory : public McDefaultBeanFactory {
    Q_OBJECT

public:
	/*	构造函数，传入一个reader，并调用read方法注册bean
		本对象析构时会自动析构reader，故无需为为reader指定父对象
	*/
    explicit McXmlBeanFactory(IMcBeanDefinitionReader *reader, QObject *parent = nullptr);
	virtual ~McXmlBeanFactory();

private:
	QScopedPointer<McXmlBeanFactoryData> d;
};
