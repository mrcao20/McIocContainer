#pragma once

#include <qmetatype.h>
#include <QVariant>
#include <QSharedPointer>

#include "../McMacroGlobal.h"

#define MC_DECLARE_METATYPE(Class)  \
    Q_DECLARE_METATYPE(QSharedPointer<Class>)

#define MC_DECL_STATIC(Class)	\
    static const int Class##_Static_Init;

#define MC_STATIC(Class)	\
	const int Class::Class##_Static_Init = []() -> int {

#define MC_STATIC_END()	\
	return 0;}();

#define MC_DEFINE_TYPELIST(...)    \
public: \
    using McPrivateTypeList = McPrivate::McTypeList<__VA_ARGS__>;    \
private:

#define MC_TYPELIST(Class)   \
    Class, Class::McPrivateTypeList

#define MC_DECL_TYPELIST(Class) MC_TYPELIST(Class)

namespace McPrivate {

template <typename...> struct McTypeList;

template <typename T, typename... U>
struct McTypeList<T, U...> {
    using Head = T;
    using Tails = McTypeList<U...>;
};

// 针对空list的特化
template <>
struct McTypeList<> {};

template<typename From, typename To>
struct McRegisterConverterHelper {
    static void registerConverter(){
        if (!QMetaType::hasRegisteredConverterFunction<QSharedPointer<From>, QSharedPointer<To>>()) {
            QMetaType::registerConverter<QSharedPointer<From>, QSharedPointer<To>>();
        }
    }
};

template<typename From, typename... Tos>
struct McRegisterConverterHelper<From, McPrivate::McTypeList<Tos...>> {
    static void registerConverter(){
        using TypeList = McPrivate::McTypeList<Tos...>;
        McRegisterConverterHelper<From, typename TypeList::Head>::registerConverter();
        McRegisterConverterHelper<From, typename TypeList::Tails>::registerConverter();
    }
};

template<typename From>
struct McRegisterConverterHelper<From, QObject> {
    static void registerConverter(){
    }
};

template<typename From>
struct McRegisterConverterHelper<From, McPrivate::McTypeList<>> {
    static void registerConverter(){
    }
};

}

template<typename From, typename To>
To mcConverterQSharedPointerObject(const From &from) {
    return from.template objectCast<typename To::Type>();
}

template<typename T>
int mcRegisterBeanFactory(const char *typeName = Q_NULLPTR) {
    Q_STATIC_ASSERT_X(!std::is_pointer<T>::value, "mcRegisterBeanFactory's template type must not be a pointer type");
    if (!QMetaType::hasRegisteredConverterFunction<QSharedPointer<T>, QSharedPointer<QObject>>()) {
        QMetaType::registerConverter<QSharedPointer<T>, QSharedPointer<QObject>>();
    }
    if (!QMetaType::hasRegisteredConverterFunction<QSharedPointer<QObject>, QSharedPointer<T>>()) {
        QMetaType::registerConverter<QSharedPointer<QObject>, QSharedPointer<T>>(mcConverterQSharedPointerObject<QSharedPointer<QObject>, QSharedPointer<T>>);
    }
    if (typeName == Q_NULLPTR) {
        return qRegisterMetaType<T*>();
    }
    else {
        return qRegisterMetaType<T*>(typeName);
    }
}

template<typename From, typename To>
int mcRegisterBeanFactory(const char *typeName = Q_NULLPTR) {
    int typeId = mcRegisterBeanFactory<From>(typeName);
    Q_STATIC_ASSERT_X(!std::is_pointer<To>::value, "mcRegisterBeanFactory's template type must not be a pointer type");
    McPrivate::McRegisterConverterHelper<From, To>::registerConverter();
	return typeId;
}

template<typename From, typename To>
To mcConverterQVariantList(const From &from) {
	To to;
	for (const auto &f : from) {
        to << f.template value<typename To::value_type>();
	}
	return to;
}

template<typename From, typename To>
void mcRegisterQVariantListConverter() {
	if (QMetaType::hasRegisteredConverterFunction(qMetaTypeId<From>(), qMetaTypeId<To>()))
		return;
	QMetaType::registerConverter<From, To>(mcConverterQVariantList<From, To>);
}

template<typename T>
void mcRegisterQVariantListConverter() {
	mcRegisterQVariantListConverter<QVariantList, T>();
}

template<typename From, typename To>
To mcConverterList(const From &from) {
	To to;
	for (const auto &f : from) {
        to << QVariant::fromValue(f).template value<typename To::value_type>();
	}
	return to;
}

template<typename From, typename To>
void mcRegisterListConverter() {
	if (QMetaType::hasRegisteredConverterFunction(qMetaTypeId<From>(), qMetaTypeId<To>()))
		return;
	QMetaType::registerConverter<From, To>(mcConverterList<From, To>);
}

template<typename T>
void mcRegisterListObjectConverter() {
	mcRegisterListConverter<T, QList<QObject *>>();
}

template<typename From, typename To>
To mcConverterQVariantMap(const From &from) {
	To to;
    using keyType = typename To::key_type;
    using mappedType = typename To::mapped_type;
	for (auto itr = from.cbegin(); itr != from.cend(); ++itr) {
        keyType key = itr.key().template value<keyType>();
        mappedType value = itr.value().template value<mappedType>();
		to.insert(key, value);
	}
	return to;
}

template<typename From, typename To>
void mcRegisterQVariantMapConverter() {
	if (QMetaType::hasRegisteredConverterFunction(qMetaTypeId<From>(), qMetaTypeId<To>()))
		return;
	QMetaType::registerConverter<From, To>(mcConverterQVariantMap<From, To>);
}

template<typename T>
void mcRegisterQVariantMapConverter() {
	mcRegisterQVariantMapConverter<QMap<QVariant, QVariant>, T>();
}

namespace Mc {
namespace Ioc {

template<typename From, typename To>
struct McRegisterConverterHelper {
    static void registerConverter() {
    }
};

template<typename From, typename To>
void mcRegisterConverter() {
    McRegisterConverterHelper<From, To>::registerConverter();
}

template<typename T>
void mcRegisterListConverter() {
	mcRegisterConverter<QVariantList, T>();
}

template<typename T>
void mcRegisterMapConverter() {
	mcRegisterConverter<QMap<QVariant, QVariant>, T>();
}

MCIOCCONTAINER_EXPORT void mcInitContainer() noexcept;

MCIOCCONTAINER_EXPORT void connect(const QString &beanName
                                   , const QString &sender
                                   , const QString &signal
                                   , const QString &receiver
                                   , const QString &slot
                                   , Qt::ConnectionType type = Qt::AutoConnection) noexcept;

}
}
