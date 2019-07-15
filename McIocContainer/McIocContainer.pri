
HEADERS += ../include/McContainerGlobal.h \
    $$PWD/../include/McBeanReference.h \
    ../include/McIocContainer.h \
    ../include/McBeanGlobal.h \
    ../include/IMcBeanDefinition.h \
    ../include/IMcBeanDefinitionRegistry.h \
    ../include/McRootBeanDefinition.h \
    ../include/IMcBeanFactory.h \
    ../include/IMcConfigurableBeanFactory.h \
    ../include/McAbstractBeanFactory.h \
    ../include/McDefaultBeanFactory.h \
    ../include/McXmlBeanFactory.h \
    ../include/IMcPropertyParser.h \
    ../include/IMcPropertyParserCollection.h \
    ../include/McPropertyParserPlugins.h \
    ../include/IMcBeanDefinitionReader.h \
    ../include/McAbstractBeanDefinitionReader.h \
    ../include/McXmlBeanDefinitionReader.h \
    ../include/IMcBeanReferenceResolver.h \
    ../include/IMcApplicationContext.h \
    ../include/McAbstractApplicationContext.h \
    ../include/McDefaultApplicationContext.h \
    ../include/McXmlApplicationContext.h \
    ../include/McMacroGlobal.h
SOURCES += ./McIocContainer.cpp \
    ./McBeanGlobal.cpp \
    ./McAbstractBeanFactory.cpp \
    ./McDefaultBeanFactory.cpp \
    ./McXmlBeanFactory.cpp \
    ./McPropertyParserPlugins.cpp \
    ./McAbstractBeanDefinitionReader.cpp \
    ./McXmlBeanDefinitionReader.cpp \
    ./McAbstractApplicationContext.cpp \
    ./McDefaultApplicationContext.cpp \
    ./McXmlApplicationContext.cpp
