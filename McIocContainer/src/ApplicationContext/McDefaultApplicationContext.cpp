#include "include/ApplicationContext/impl/McDefaultApplicationContext.h"

#include "include/BeanFactory/impl/McDefaultBeanFactory.h"

McDefaultApplicationContext::McDefaultApplicationContext(QObject *parent)
    : McDefaultApplicationContext(QSharedPointer<IMcConfigurableBeanFactory>(new McDefaultBeanFactory()), parent)
{
}

McDefaultApplicationContext::McDefaultApplicationContext(const QSharedPointer<IMcConfigurableBeanFactory>& factory
	, QObject *parent)
	: McAbstractApplicationContext(factory, parent)
{
}

McDefaultApplicationContext::~McDefaultApplicationContext(){
}
