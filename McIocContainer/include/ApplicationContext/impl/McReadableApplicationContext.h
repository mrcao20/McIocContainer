#pragma once

#include "../IMcReadableApplicationContext.h"
#include "McAbstractApplicationContext.h"

class IMcBeanDefinitionReader;

struct McReadableApplicationContextData;

class McReadableApplicationContext
    : public McAbstractApplicationContext
    , MC_IMPLEMENTS IMcReadableApplicationContext {
    Q_OBJECT
public:
    McReadableApplicationContext(const QSharedPointer<IMcConfigurableBeanFactory> &factory
                                 , const QSharedPointer<IMcBeanDefinitionReader> &reader
                                 , QObject *parent = nullptr);
    ~McReadableApplicationContext() override;

private:
    QScopedPointer<McReadableApplicationContextData> d;
};
