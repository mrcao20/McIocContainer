#include "../include/McDefaultApplicationContext.h"

#include "../include/McDefaultBeanFactory.h"

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
