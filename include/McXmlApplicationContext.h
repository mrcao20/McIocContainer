#ifndef _MC_XML_APPLICATION_CONTEXT_H_
#define _MC_XML_APPLICATION_CONTEXT_H_

#include "McDefaultApplicationContext.h"

class IMcBeanDefinitionReader;
class McXmlBeanFactory;

class MCIOCCONTAINER_EXPORT McXmlApplicationContext : public McDefaultApplicationContext {
	Q_OBJECT;

public:
	McXmlApplicationContext(const QString &location, QObject *parent = 0);
	McXmlApplicationContext(IMcBeanDefinitionReader *reader, QObject *parent = 0);
	McXmlApplicationContext(McXmlBeanFactory *factory, QObject *parent = 0);
	virtual ~McXmlApplicationContext();
};

#endif // !_MC_XML_APPLICATION_CONTEXT_H_