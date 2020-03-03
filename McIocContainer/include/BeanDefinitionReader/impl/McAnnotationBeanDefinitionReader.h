#pragma once

#include "McAbstractBeanDefinitionReader.h"

struct McAnnotationBeanDefinitionReaderData;

class IMcBeanDefinition;

class MCIOCCONTAINER_EXPORT McAnnotationBeanDefinitionReader : public McAbstractBeanDefinitionReader {
    Q_OBJECT
public:
    McAnnotationBeanDefinitionReader(
            const QHash<QString, QSharedPointer<IMcBeanDefinition>> &definitions
            , QObject *parent = nullptr);
    ~McAnnotationBeanDefinitionReader() override;
    
    void readBeanDefinition(const QSharedPointer<IMcBeanDefinitionRegistry>& registry) noexcept override;
    
private:
    void inject(const QString& beanName, const QSharedPointer<IMcBeanDefinition>& beanDefinition);
    void injectProperty(const QMetaObject *metaObj, const QSharedPointer<IMcBeanDefinition>& beanDefinition);
    
private:
    QScopedPointer<McAnnotationBeanDefinitionReaderData> d;
};
