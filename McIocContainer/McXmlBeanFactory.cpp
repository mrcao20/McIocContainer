#include "../include/McXmlBeanFactory.h"

#include "../include/IMcBeanDefinitionReader.h"

struct McXmlBeanFactoryData {
};

McXmlBeanFactory::McXmlBeanFactory(QObject *parent)
	: McDefaultBeanFactory(parent)
	, d(new McXmlBeanFactoryData())
{
}

McXmlBeanFactory::~McXmlBeanFactory(){
}
