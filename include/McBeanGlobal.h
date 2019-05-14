#ifndef _MC_BEAN_GLOBAL_H_
#define _MC_BEAN_GLOBAL_H_

#include <qmetatype.h>
#include <QVariant>

#define MC_DECL_STATIC(Class)	\
	static const int Class##_Static_Init;

#define MC_STATIC(Class)	\
	const int Class::Class##_Static_Init = []() -> int {

#define MC_STATIC_END	\
	return 0;}();

void mcInitContainer();

template<typename T>
int mcRegisterBeanFactory(const char *typeName = Q_NULLPTR) {
	if (typeName == Q_NULLPTR) {
		return qRegisterMetaType<T>();
	}
	else {
		return qRegisterMetaType<T>(typeName);
	}
}

template<typename From, typename To>
int mcRegisterBeanFactory(const char *typeName = Q_NULLPTR) {
	QMetaType::registerConverter<From, To>();
	int typeId = mcRegisterBeanFactory<From>(typeName);
	return typeId;
}

template<typename From, typename To>
To mcConverterQVariantList(const From &from) {
	To to;
	for (const auto &f : from) {
		to << f.value<To::value_type>();
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
		to << QVariant::fromValue(f).value<To::value_type>();
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
	using keyType = To::key_type;
	using mappedType = To::mapped_type;
	for (auto itr = from.cbegin(); itr != from.cend(); ++itr) {
		keyType key = itr.key().value<keyType>();
		mappedType value = itr.value().value<mappedType>();
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

#endif // !_MC_BEAN_GLOBAL_H_