#-------------------------------------------------
#
# Project created by QtCreator 2019-06-18T16:52:31
#
#-------------------------------------------------

QT += core xml

TARGET = McParserPlugin
TEMPLATE = lib

DEFINES += MCPARSERPLUGIN_LIB

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=

HEADERS +=

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(McParserPlugin.pri)



unix:!macx: LIBS += -L$$PWD/../build/build-McIocContainer-Qt_5_8_0_Qt_5_8_0-Debug/McIocContainer/ -lMcIocContainer

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
