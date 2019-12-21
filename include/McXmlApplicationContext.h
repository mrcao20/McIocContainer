#pragma once

#include "McDefaultApplicationContext.h"

class IMcBeanDefinitionReader;
class McXmlBeanFactory;

class MCIOCCONTAINER_EXPORT McXmlApplicationContext : public McDefaultApplicationContext {
    Q_OBJECT

public:
    McXmlApplicationContext(const QString &location, QObject *parent = nullptr);
    McXmlApplicationContext(IMcBeanDefinitionReader *reader, QObject *parent = nullptr);
    McXmlApplicationContext(McXmlBeanFactory *factory, QObject *parent = nullptr);
	virtual ~McXmlApplicationContext();
};
