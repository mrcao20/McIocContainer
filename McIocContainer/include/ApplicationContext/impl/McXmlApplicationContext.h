#pragma once

#include "McDefaultApplicationContext.h"

#include <QSharedPointer>

class IMcBeanDefinitionReader;
class McXmlBeanFactory;

class MCIOCCONTAINER_EXPORT McXmlApplicationContext : public McDefaultApplicationContext {
    Q_OBJECT

public:
    McXmlApplicationContext(const QString &location, QObject *parent = nullptr);
    McXmlApplicationContext(const QSharedPointer<IMcBeanDefinitionReader>& reader, QObject *parent = nullptr);
    McXmlApplicationContext(const QSharedPointer<IMcConfigurableBeanFactory>& factory, const QSharedPointer<IMcBeanDefinitionReader>& reader, QObject *parent = nullptr);
    virtual ~McXmlApplicationContext();
};
