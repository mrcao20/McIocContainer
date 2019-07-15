#include "../include/McDefaultApplicationContext.h"

#include "../include/McDefaultBeanFactory.h"

McDefaultApplicationContext::McDefaultApplicationContext(QObject *parent)
	: McDefaultApplicationContext(new McDefaultBeanFactory(), parent)
{
}

McDefaultApplicationContext::McDefaultApplicationContext(IMcConfigurableBeanFactory *factory
	, QObject *parent)
	: McAbstractApplicationContext(factory, parent)
{
}

McDefaultApplicationContext::~McDefaultApplicationContext(){
}
