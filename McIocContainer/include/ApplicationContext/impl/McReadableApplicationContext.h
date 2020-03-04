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
    McReadableApplicationContext(const QSharedPointer<IMcBeanDefinitionReader> &reader
                                 , QObject *parent = nullptr);
    ~McReadableApplicationContext() override;
    
    void readBeans() noexcept override;
    
protected:
    void doRefresh() noexcept override;

private:
    QScopedPointer<McReadableApplicationContextData> d;
};
