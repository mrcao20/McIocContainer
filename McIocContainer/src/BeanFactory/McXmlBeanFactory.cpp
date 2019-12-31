#include "include/BeanFactory/impl/McXmlBeanFactory.h"

#include "include/BeanDefinitionReader/IMcBeanDefinitionReader.h"

struct McXmlBeanFactoryData {
};

McXmlBeanFactory::McXmlBeanFactory(QObject *parent)
	: McDefaultBeanFactory(parent)
	, d(new McXmlBeanFactoryData())
{
}

McXmlBeanFactory::~McXmlBeanFactory(){
}
