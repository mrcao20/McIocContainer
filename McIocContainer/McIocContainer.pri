HEADERS += \
    $$PWD/include/ApplicationContext/IMcApplicationContext.h \
    $$PWD/include/ApplicationContext/IMcReadableApplicationContext.h \
    $$PWD/include/ApplicationContext/IMcRefreshableApplicationContext.h \
    $$PWD/include/ApplicationContext/McContainerGlobal.h \
    $$PWD/include/ApplicationContext/impl/McAbstractApplicationContext.h \
    $$PWD/include/ApplicationContext/impl/McAnnotationApplicationContext.h \
    $$PWD/include/ApplicationContext/impl/McDefaultApplicationContext.h \
    $$PWD/include/ApplicationContext/impl/McReadableApplicationContext.h \
    $$PWD/include/ApplicationContext/impl/McXmlApplicationContext.h \
    $$PWD/include/BeanDefinition/IMcBeanDefinition.h \
    $$PWD/include/BeanDefinition/impl/McRootBeanDefinition.h \
    $$PWD/include/BeanDefinitionReader/IMcBeanDefinitionReader.h \
    $$PWD/include/BeanDefinitionReader/impl/McAbstractBeanDefinitionReader.h \
    $$PWD/include/BeanDefinitionReader/impl/McAnnotationBeanDefinitionReader.h \
    $$PWD/include/BeanDefinitionReader/impl/McXmlBeanDefinitionReader.h \
    $$PWD/include/BeanFactory/IMcBeanDefinitionRegistry.h \
    $$PWD/include/BeanFactory/IMcBeanFactory.h \
    $$PWD/include/BeanFactory/IMcBeanReferenceResolver.h \
    $$PWD/include/BeanFactory/IMcConfigurableBeanFactory.h \
    $$PWD/include/BeanFactory/McBeanGlobal.h \
    $$PWD/include/BeanFactory/McBeanGlobal.h \
    $$PWD/include/BeanFactory/impl/McAbstractBeanFactory.h \
    $$PWD/include/BeanFactory/impl/McBeanConnector.h \
    $$PWD/include/BeanFactory/impl/McBeanReference.h \
    $$PWD/include/BeanFactory/impl/McDefaultBeanFactory.h \
    $$PWD/include/McGlobal.h \
    $$PWD/include/McIocBoot.h \
    $$PWD/include/McIocVersion.h \
    $$PWD/include/McMacroGlobal.h \
    $$PWD/include/Middleware/Transfer/IMcControllerContainer.h \
    $$PWD/include/Middleware/Transfer/IMcQmlSocketContainer.h \
    $$PWD/include/Middleware/Transfer/impl/McControllerContainer.h \
    $$PWD/include/Middleware/Transfer/impl/McModelContainer.h \
    $$PWD/include/Middleware/Transfer/impl/McRequestRunner.h \
    $$PWD/include/Middleware/Transfer/impl/McRequestor.h \
    $$PWD/include/Middleware/Transfer/impl/McResponse.h \
    $$PWD/include/Middleware/Transfer/impl/qs/McInnerSocket.h \
    $$PWD/include/Middleware/Transfer/impl/qs/McQmlSocket.h \
    $$PWD/include/Middleware/Transfer/impl/qs/McQmlSocketContainer.h \
    $$PWD/include/Middleware/Transfer/impl/qs/McQmlSocketRunner.h \
    $$PWD/include/Middleware/Transfer/impl/qs/McSession.h \
    $$PWD/include/Middleware/Utils/McJsonUtils.h \
    $$PWD/include/Middleware/Utils/McRestResponse.h \
    $$PWD/include/Middleware/Utils/McUtils.h \
    $$PWD/include/PropertyParser/IMcPropertyParser.h \
    $$PWD/include/PropertyParser/IMcPropertyParserCollection.h \ \
    $$PWD/include/PropertyParser/impl/McPropertyParserPlugins.h

SOURCES += \
    $$PWD/src/ApplicationContext/McAbstractApplicationContext.cpp \
    $$PWD/src/ApplicationContext/McAnnotationApplicationContext.cpp \
    $$PWD/src/ApplicationContext/McDefaultApplicationContext.cpp \
    $$PWD/src/ApplicationContext/McReadableApplicationContext.cpp \
    $$PWD/src/ApplicationContext/McXmlApplicationContext.cpp \
    $$PWD/src/BeanDefinitionReader/McAbstractBeanDefinitionReader.cpp \
    $$PWD/src/BeanDefinitionReader/McAnnotationBeanDefinitionReader.cpp \
    $$PWD/src/BeanDefinitionReader/McXmlBeanDefinitionReader.cpp \
    $$PWD/src/BeanFactory/McAbstractBeanFactory.cpp \
    $$PWD/src/BeanFactory/McBeanConnector.cpp \
    $$PWD/src/BeanFactory/McBeanGlobal.cpp \
    $$PWD/src/BeanFactory/McBeanReference.cpp \
    $$PWD/src/BeanFactory/McDefaultBeanFactory.cpp \
    $$PWD/src/McGlobal.cpp \
    $$PWD/src/McIocBoot.cpp \
    $$PWD/src/Middleware/Transfer/McControllerContainer.cpp \
    $$PWD/src/Middleware/Transfer/McModelContainer.cpp \
    $$PWD/src/Middleware/Transfer/McRequestRunner.cpp \
    $$PWD/src/Middleware/Transfer/McRequestor.cpp \
    $$PWD/src/Middleware/Transfer/McResponse.cpp \
    $$PWD/src/Middleware/Transfer/qs/McInnerSocket.cpp \
    $$PWD/src/Middleware/Transfer/qs/McQmlSocket.cpp \
    $$PWD/src/Middleware/Transfer/qs/McQmlSocketContainer.cpp \
    $$PWD/src/Middleware/Transfer/qs/McQmlSocketRunner.cpp \
    $$PWD/src/Middleware/Transfer/qs/McSession.cpp \
    $$PWD/src/Middleware/Utils/McJsonUtils.cpp \
    $$PWD/src/Middleware/Utils/McUtils.cpp \
    $$PWD/src/PropertyParser/McPropertyParserPlugins.cpp

RESOURCES += \
    $$PWD/qrc/Resource.qrc
