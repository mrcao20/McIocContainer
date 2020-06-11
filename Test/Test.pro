QT += quick xml core concurrent
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        HelloWorld.cpp \
        ListModel.cpp \
        MacroTest.cpp \
        QmlSocketTest.cpp \
        ReferenceBean.cpp \
        a.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml \
    xmltest2.xml

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

HEADERS += \
    HelloWorld.h \
    IHelloWorld.h \
    IRR.h \
    IReferenceBean.h \
    ListModel.h \
    MacroTest.h \
    QmlSocketTest.h \
    ReferenceBean.h \
    a.h

INCLUDEPATH += $$PWD/../McIocContainer/include
DEPENDPATH += $$PWD/../McIocContainer/include

CONFIG(debug, debug|release) {
    win32: LIBS += -L$$PWD/../build/build-McIocContainer-Desktop_Qt_5_12_3_MinGW_64_bit-Debug/McIocContainer/debug/ -lMcIocContainer
    else:unix: LIBS += -L$$PWD/../build/build-McIocContainer-Desktop_Qt_5_12_6_GCC_64bit-Debug/McIocContainer/ -lMcIocContainer
} else {
    win32: LIBS += -L$$PWD/../build/build-McIocContainer-Desktop_Qt_5_12_3_MinGW_64_bit-Release/McIocContainer/release/ -lMcIocContainer
    else:unix: LIBS += -L$$PWD/../build/build-McIocContainer-Desktop_Qt_5_12_6_GCC_64bit-Release/McIocContainer/ -lMcIocContainer
}
