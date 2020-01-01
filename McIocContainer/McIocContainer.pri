HEADERS += \
    $$PWD/include/ApplicationContext/IMcApplicationContext.h \
    $$PWD/include/ApplicationContext/IMcReadableApplicationContext.h \
    $$PWD/include/ApplicationContext/impl/McAbstractApplicationContext.h \
    $$PWD/include/ApplicationContext/impl/McDefaultApplicationContext.h \
    $$PWD/include/ApplicationContext/impl/McReadableApplicationContext.h \
    $$PWD/include/ApplicationContext/impl/McXmlApplicationContext.h \
    $$PWD/include/BeanDefinition/IMcBeanDefinition.h \
    $$PWD/include/BeanDefinition/impl/McRootBeanDefinition.h \
    $$PWD/include/BeanDefinitionReader/IMcBeanDefinitionReader.h \
    $$PWD/include/BeanDefinitionReader/impl/McAbstractBeanDefinitionReader.h \
    $$PWD/include/BeanDefinitionReader/impl/McXmlBeanDefinitionReader.h \
    $$PWD/include/BeanFactory/IMcBeanDefinitionRegistry.h \
    $$PWD/include/BeanFactory/IMcBeanFactory.h \
    $$PWD/include/BeanFactory/IMcBeanReferenceResolver.h \
    $$PWD/include/BeanFactory/IMcConfigurableBeanFactory.h \
    $$PWD/include/BeanFactory/impl/McAbstractBeanFactory.h \
    $$PWD/include/BeanFactory/impl/McBeanReference.h \
    $$PWD/include/BeanFactory/impl/McDefaultBeanFactory.h \
    $$PWD/include/McIocContainer.h \
    $$PWD/include/McIocVersion.h \
    $$PWD/include/McMacroGlobal.h \
    $$PWD/include/PropertyParser/IMcPropertyParser.h \
    $$PWD/include/PropertyParser/IMcPropertyParserCollection.h \ \
    $$PWD/include/PropertyParser/impl/McPropertyParserPlugins.h

SOURCES += \
    $$PWD/src/ApplicationContext/McAbstractApplicationContext.cpp \
    $$PWD/src/ApplicationContext/McDefaultApplicationContext.cpp \
    $$PWD/src/ApplicationContext/McReadableApplicationContext.cpp \
    $$PWD/src/ApplicationContext/McXmlApplicationContext.cpp \
    $$PWD/src/BeanDefinitionReader/McAbstractBeanDefinitionReader.cpp \
    $$PWD/src/BeanDefinitionReader/McXmlBeanDefinitionReader.cpp \
    $$PWD/src/BeanFactory/McAbstractBeanFactory.cpp \
    $$PWD/src/BeanFactory/McBeanGlobal.cpp \
    $$PWD/src/BeanFactory/McDefaultBeanFactory.cpp \
    $$PWD/src/McIocContainer.cpp \
    $$PWD/src/PropertyParser/McPropertyParserPlugins.cpp
