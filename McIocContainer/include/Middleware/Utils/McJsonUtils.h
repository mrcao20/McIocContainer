#pragma once

#include <qobject.h>
#include <qstring.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <QVariant>

#include "McRestResponse.h"

class McJsonUtils {
public:
	static QJsonObject objToJson(QObject *obj) noexcept;
	static QJsonObject gadgetToJson(void *gadget, const QMetaObject *mobj) noexcept;

	template<typename T>
	static QJsonObject responseToJson(const McRestResponse<T> &response) noexcept;

private:
	static bool isPointer(const QString &typeName) noexcept;
	static bool isListPointer(const QString &typeName) noexcept;
};


template<typename T, int =
	QtPrivate::IsPointerToTypeDerivedFromQObject<T>::Value ? QMetaType::PointerToQObject :
	QtPrivate::IsGadgetHelper<T>::IsRealGadget ? QMetaType::IsGadget :
	QtPrivate::IsPointerToGadgetHelper<T>::IsRealGadget ? QMetaType::PointerToGadget : 0>
	struct McJsonTypeSelector {
	static QJsonValue toJsonValue(const T &value) {
        Q_UNUSED(value)
		return QJsonValue();
	}
};
template<>
struct McJsonTypeSelector<QString> {
	static QJsonValue toJsonValue(const QString &value) {
		return QJsonValue(value);
	}
};
template<>
struct McJsonTypeSelector<bool> {
	static QJsonValue toJsonValue(bool value) {
		return QJsonValue(value);
	}
};
template<>
struct McJsonTypeSelector<double> {
	static QJsonValue toJsonValue(double value) {
		return QJsonValue(value);
	}
};
template<>
struct McJsonTypeSelector<int> {
	static QJsonValue toJsonValue(int value) {
		return QJsonValue(value);
	}
};
template<>
struct McJsonTypeSelector<qint64> {
	static QJsonValue toJsonValue(qint64 value) {
		return QJsonValue(value);
	}
};
template<>
struct McJsonTypeSelector<const char *> {
	static QJsonValue toJsonValue(const char *value) {
		return QJsonValue(value);
	}
};
template<typename T>
struct McJsonTypeSelector<T *, QMetaType::PointerToQObject> {
	static QJsonValue toJsonValue(T *value) {
		return QJsonValue(McJsonUtils::objToJson(qobject_cast<QObject *>(value)));
	}
};
template<typename T>
struct McJsonTypeSelector<T, QMetaType::IsGadget> {
	static QJsonValue toJsonValue(const T &value) {
		return QJsonValue(McJsonUtils::gadgetToJson(static_cast<void*>(&value), T::staticMetaObject));
	}
};
template<typename T>
struct McJsonTypeSelector<T *, QMetaType::PointerToGadget> {
	static QJsonValue toJsonValue(T *value) {
		if (!value)
			return QJsonValue();
		return QJsonValue(McJsonUtils::gadgetToJson(static_cast<void*>(value), T::staticMetaObject));
	}
};
template<typename T>
struct McJsonTypeSelector<QList<T>, 0> {
	static QJsonValue toJsonValue(const QList<T> &value) {
		QJsonArray jsonArray;
		for (const auto &v : value) {
			jsonArray.append(McJsonTypeSelector<T>::toJsonValue(v));
		}
		return QJsonValue(jsonArray);
	}
};
template<typename T1, typename T2>
struct McJsonTypeSelector<QMap<T1, T2>, 0> {
	static QJsonValue toJsonValue(const QMap<T1, T2> &value) {
		QJsonArray jsonArray;
		auto itrEnd = value.cend();
		for (auto itr = value.cbegin(); itr != itrEnd; ++itr) {
			QJsonObject jsonObj;
			jsonObj.insert(QVariant(itr.key()).toString(), McJsonTypeSelector<T2>::toJsonValue(itr.value()));
			jsonArray.append(jsonObj);
		}
		return QJsonValue(jsonArray);
	}
};

template<typename T>
QJsonObject McJsonUtils::responseToJson(const McRestResponse<T> &response) noexcept {
	QJsonObject jsonObj;
	jsonObj.insert("success", QJsonValue(response.m_success));
	jsonObj.insert("msg", QJsonValue(response.m_msg));
	QJsonValue payloadValue;
	if (response.m_success)
		payloadValue = McJsonTypeSelector<T>::toJsonValue(response.m_payload);
	jsonObj.insert("payload", payloadValue);
	return jsonObj;
}
