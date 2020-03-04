#include "include/ApplicationContext/impl/McAnnotationApplicationContext.h"

#include <QDebug>

#include "include/BeanDefinitionReader/impl/McAnnotationBeanDefinitionReader.h"
#include "include/BeanDefinition/impl/McRootBeanDefinition.h"
#include "include/BeanFactory/impl/McBeanConnector.h"
#include "include/McMacroGlobal.h"

MC_DECLARE_PRIVATE_DATA(McAnnotationApplicationContext)
static QHash<QString, QSharedPointer<IMcBeanDefinition>> autowiredRegistry;	// 用来保存需要自动注入的bean的beanName和BeanDefinition
MC_DECLARE_PRIVATE_DATA_END()

QHash<QString, QSharedPointer<IMcBeanDefinition>> MC_PRIVATE_DATA_NAME(McAnnotationApplicationContext)::autowiredRegistry = QHash<QString, QSharedPointer<IMcBeanDefinition>>();

#define globalDefinitions() (MC_PRIVATE_DATA_NAME(McAnnotationApplicationContext)::autowiredRegistry)

McAnnotationApplicationContext::McAnnotationApplicationContext(IMcConfigurableBeanFactoryConstPtrRef factory
        , IMcBeanDefinitionReaderConstPtrRef reader
        , QObject *parent)
    : McReadableApplicationContext(factory, reader, parent)
    , MC_NEW_PRIVATE_DATA(McAnnotationApplicationContext)
{
}

McAnnotationApplicationContext::McAnnotationApplicationContext(QObject *parent)
    : McReadableApplicationContext(
          IMcBeanDefinitionReaderPtr(new McAnnotationBeanDefinitionReader(globalDefinitions()))
          , parent)
    , MC_NEW_PRIVATE_DATA(McAnnotationApplicationContext)
{
}

McAnnotationApplicationContext::~McAnnotationApplicationContext() {
}

void McAnnotationApplicationContext::insertRegistry(const QString &typeName
                                                    , const QString &beanName
                                                    , bool isSingleton) noexcept {
    
    auto beanDefinition = globalDefinitions()[beanName];
    if(!beanDefinition) {
        beanDefinition = QSharedPointer<McRootBeanDefinition>::create();
        globalDefinitions()[beanName] = beanDefinition;
    }
    if(!beanDefinition->getClassName().isEmpty()) {
        qCritical() << "injected fail. the beanName is exists. it's typeName is" << beanDefinition->getClassName()
                    << ". want inject typeName:" << typeName << "beanName:" << beanName;
        return;
    }
    beanDefinition->setClassName(typeName);
    beanDefinition->setSingleton(isSingleton);
}

void McAnnotationApplicationContext::addConnect(
        const QString &beanName
        , const QString &sender
        , const QString &signal
        , const QString &receiver
        , const QString &slot
        , Qt::ConnectionType type) noexcept {
    
    auto beanDefinition = globalDefinitions()[beanName];
    if(!beanDefinition) {
        beanDefinition = QSharedPointer<McRootBeanDefinition>::create();
        globalDefinitions()[beanName] = beanDefinition;
    }
    McBeanConnectorPtr connector = McBeanConnectorPtr::create();
    connector->setSender(sender);
    connector->setSignal(signal);
    connector->setReceiver(receiver);
    connector->setSlot(slot);
    connector->setType(type);
    QVariant var;
    var.setValue(connector);
    beanDefinition->addConnector(var);
}
