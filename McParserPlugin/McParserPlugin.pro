#-------------------------------------------------
#
# Project created by QtCreator 2019-06-18T16:52:31
#
#-------------------------------------------------

QT += core xml

CONFIG(debug, debug|release) {
    TARGET = McParserPlugind
} else {
    TARGET = McParserPlugin
}

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

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

CONFIG(debug, debug|release) {
    win32: LIBS += -L$$PWD/../build/build-McIocContainer-Desktop_Qt_5_12_3_MinGW_64_bit-Debug/McIocContainer/debug/ -lMcIocContainer
    else:unix: LIBS += -L$$PWD/../build/build-McIocContainer-Desktop_Qt_5_12_3_MinGW_64_bit-Release/McIocContainer/ -lMcIocContainer
    win32:DESTDIR += $$PWD/../build/build-McIocContainer-Desktop_Qt_5_12_3_MinGW_64_bit-Debug/Test/debug/plugins/McIocContainer/
} else {
    win32: LIBS += -L$$PWD/../build/build-McIocContainer-Desktop_Qt_5_12_3_MinGW_64_bit-Release/McIocContainer/release/ -lMcIocContainer
    else:unix: LIBS += -L$$PWD/../build/build-McIocContainer-Desktop_Qt_5_12_3_MinGW_64_bit-Release/McIocContainer/ -lMcIocContainer
    win32:DESTDIR += $$PWD/../build/build-McIocContainer-Desktop_Qt_5_12_3_MinGW_64_bit-Release\Test\release\plugins\McIocContainer
}


