#pragma once

#include "McReadableApplicationContext.h"

#include <QSharedPointer>

class IMcBeanDefinitionReader;

class MCIOCCONTAINER_EXPORT McXmlApplicationContext : public McReadableApplicationContext {
    Q_OBJECT
public:
    McXmlApplicationContext(const QString &location, QObject *parent = nullptr);
    McXmlApplicationContext(const QStringList &locations, QObject *parent = nullptr);
    McXmlApplicationContext(const QSharedPointer<IMcBeanDefinitionReader>& reader
                            , QObject *parent = nullptr);
    McXmlApplicationContext(const QSharedPointer<IMcConfigurableBeanFactory>& factory
                            , const QSharedPointer<IMcBeanDefinitionReader>& reader
                            , QObject *parent = nullptr);
    ~McXmlApplicationContext() override;
};
