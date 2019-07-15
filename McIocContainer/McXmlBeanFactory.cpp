#include "../include/McXmlBeanFactory.h"

#include "../include/IMcBeanDefinitionReader.h"

struct McXmlBeanFactoryData {
	IMcBeanDefinitionReader *reader{ Q_NULLPTR };

	~McXmlBeanFactoryData() {
		MC_SAFE_DELETE(reader);
	}
};

McXmlBeanFactory::McXmlBeanFactory(IMcBeanDefinitionReader *reader, QObject *parent)
	: McDefaultBeanFactory(parent)
	, d(new McXmlBeanFactoryData())
{
	d->reader = reader;

	d->reader->readBeanDefinition(this);
}

McXmlBeanFactory::~McXmlBeanFactory(){
}
