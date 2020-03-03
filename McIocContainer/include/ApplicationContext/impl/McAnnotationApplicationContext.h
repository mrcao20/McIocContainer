#pragma once

#include "McReadableApplicationContext.h"

#include <QSharedPointer>

MC_FORWARD_DECLARE_PRIVATE_DATA(McAnnotationApplicationContext)

class MCIOCCONTAINER_EXPORT McAnnotationApplicationContext : public McReadableApplicationContext {
    Q_OBJECT
public:
    McAnnotationApplicationContext(const QSharedPointer<IMcConfigurableBeanFactory>& factory
        , const QSharedPointer<IMcBeanDefinitionReader> &reader
        , QObject *parent = nullptr);
    McAnnotationApplicationContext(QObject *parent = nullptr);
    
    ~McAnnotationApplicationContext() override;
    
    static void insertRegistry(const QString &typeName
                               , const QString &beanName
                               , bool isSingleton = true) noexcept;
    static void addConnect(const QString &beanName
                        , const QString &sender
                        , const QString &signal
                        , const QString &receiver
                        , const QString &slot
                        , Qt::ConnectionType type) noexcept;
    
private:
    MC_DECLARE_PRIVATE(McAnnotationApplicationContext)
};
