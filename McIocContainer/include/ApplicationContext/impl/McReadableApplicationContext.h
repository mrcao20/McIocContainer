#pragma once

#include "../IMcReadableApplicationContext.h"
#include "McAbstractApplicationContext.h"

class IMcBeanDefinitionReader;

class McReadableApplicationContext
    : public McAbstractApplicationContext
    , MC_IMPLEMENTS IMcReadableApplicationContext {
    Q_OBJECT
public:
    McReadableApplicationContext(const QSharedPointer<IMcConfigurableBeanFactory>& factory
                                 , const QSharedPointer<IMcBeanDefinitionReader> reader
                                 , QObject *parent = nullptr);
};
