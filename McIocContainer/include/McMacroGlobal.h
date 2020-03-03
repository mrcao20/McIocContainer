#pragma once

#include <QtCore/qglobal.h>
#include <QSharedPointer>

#ifndef BUILD_STATIC
# if defined(MCIOCCONTAINER_LIB)
#  define MCIOCCONTAINER_EXPORT Q_DECL_EXPORT
# else
#  define MCIOCCONTAINER_EXPORT Q_DECL_IMPORT
# endif
#else
# define MCIOCCONTAINER_EXPORT
#endif

//#define MC_SAFE_DELETE(p) (p) ? (delete p, p = Q_NULLPTR) : static_cast<decltype(p)>(nullptr)
//#define MC_SAFE_DELETE_QPOINTER(p) (!p.isNull()) ? (p->deleteLater()) : void()

#define MC_FORWARD_DECLARE_CLASS(Class)   \
    class Class;

#define MC_FORWARD_DECLARE_STRUCT(Class)   \
    struct Class;

#define MC_CLASS_END() };

#define MC_DECLARE_POINTER(Class) \
    using Class##Ptr = QSharedPointer<Class>; \
    using Class##ConstPtrRef = const QSharedPointer<Class> &;

#define MC_PRIVATE_DATA_NAME(Class) \
    Class##Data

#define MC_FORWARD_DECLARE_PRIVATE_DATA(Class)  \
    MC_FORWARD_DECLARE_STRUCT(MC_PRIVATE_DATA_NAME(Class))

#define MC_DECLARE_PRIVATE_DATA(Class)  \
    struct MC_PRIVATE_DATA_NAME(Class) {

#define MC_DECLARE_PRIVATE_DATA_END()   \
    MC_CLASS_END()

#define MC_DECLARE_PRIVATE(Class)   \
    QScopedPointer<MC_PRIVATE_DATA_NAME(Class)> __d__;   \
    inline MC_PRIVATE_DATA_NAME(Class) *d_func() const \
    { Q_CAST_IGNORE_ALIGN(return __d__.operator->();) }

#define MC_NEW_PRIVATE_DATA(Class)  \
    __d__(new MC_PRIVATE_DATA_NAME(Class)())

#define MC_D(Class) MC_PRIVATE_DATA_NAME(Class) *const d = d_func();

#define MC_INTERFACE class
#define MC_ABSTRACT_CLASS class
#define MC_IMPLEMENTS public

#define MC_MACRO_STR(m) #m

#define MC_PADDING_CLANG(size)  \
    char ___clang_padding___[size];

#ifndef Q_MOC_RUN			// 这行语句必须加，只有包围在这行语句之中的宏才能被识别为tag

# define MC_AUTOWIRED		// 用于表示函数是否需要自动注入

// QML Socket
# define MC_ON_OPEN
# define MC_ON_CLOSE
# define MC_ON_ERROR
# define MC_ON_MESSAGE
// end QML Socket

#endif // !Q_MOC_RUN

#define MC_COMPONENT "Component"

#define MC_CONTROLLER "Controller"
#define MC_MODEL "Model"
#define MC_QML_SOCKET "QmlSocket"

#define MC_BEANS "beans"
#define MC_BEAN "bean"
#define MC_PROPERTY "property"
#define MC_CONNECT "connect"

#define MC_THIS "this"
#define MC_SENDER "sender"
#define MC_SIGNAL "signal"
#define MC_RECEIVER "receiver"
#define MC_SLOT "slot"
#define MC_CONNECTION_TYPE "ConnectionType"
