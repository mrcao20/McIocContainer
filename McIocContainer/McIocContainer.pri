HEADERS += \
    $$PWD/include/ApplicationContext/IMcApplicationContext.h \
    $$PWD/include/ApplicationContext/McAbstractApplicationContext.h \
    $$PWD/include/ApplicationContext/McContainerGlobal.h \
    $$PWD/include/ApplicationContext/McDefaultApplicationContext.h \
    $$PWD/include/ApplicationContext/McXmlApplicationContext.h \
    $$PWD/include/BeanDefinition/IMcBeanDefinition.h \
    $$PWD/include/BeanDefinition/McRootBeanDefinition.h \
    $$PWD/include/BeanDefinitionReader/IMcBeanDefinitionReader.h \
    $$PWD/include/BeanDefinitionReader/McAbstractBeanDefinitionReader.h \
    $$PWD/include/BeanDefinitionReader/McXmlBeanDefinitionReader.h \
    $$PWD/include/BeanFactory/IMcBeanDefinitionRegistry.h \
    $$PWD/include/BeanFactory/IMcBeanFactory.h \
    $$PWD/include/BeanFactory/IMcBeanReferenceResolver.h \
    $$PWD/include/BeanFactory/IMcConfigurableBeanFactory.h \
    $$PWD/include/BeanFactory/McAbstractBeanFactory.h \
    $$PWD/include/BeanFactory/McBeanGlobal.h \
    $$PWD/include/BeanFactory/McBeanReference.h \
    $$PWD/include/BeanFactory/McDefaultBeanFactory.h \
    $$PWD/include/BeanFactory/McXmlBeanFactory.h \
    $$PWD/include/McIocContainer.h \
    $$PWD/include/McIocVersion.h \
    $$PWD/include/McMacroGlobal.h \
    $$PWD/include/PropertyParser/IMcPropertyParser.h \
    $$PWD/include/PropertyParser/IMcPropertyParserCollection.h \
    $$PWD/include/PropertyParser/McPropertyParserPlugins.h

SOURCES += \
    $$PWD/src/ApplicationContext/McAbstractApplicationContext.cpp \
    $$PWD/src/ApplicationContext/McDefaultApplicationContext.cpp \
    $$PWD/src/ApplicationContext/McXmlApplicationContext.cpp \
    $$PWD/src/BeanDefinitionReader/McAbstractBeanDefinitionReader.cpp \
    $$PWD/src/BeanDefinitionReader/McXmlBeanDefinitionReader.cpp \
    $$PWD/src/BeanFactory/McAbstractBeanFactory.cpp \
    $$PWD/src/BeanFactory/McBeanGlobal.cpp \
    $$PWD/src/BeanFactory/McDefaultBeanFactory.cpp \
    $$PWD/src/BeanFactory/McXmlBeanFactory.cpp \
    $$PWD/src/McIocContainer.cpp \
    $$PWD/src/PropertyParser/McPropertyParserPlugins.cpp
