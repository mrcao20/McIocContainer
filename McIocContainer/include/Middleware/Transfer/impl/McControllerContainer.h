#pragma once

#include <QObject>
#include "../IMcControllerContainer.h"

#include <qmap.h>

#include "include/McMacroGlobal.h"

QT_BEGIN_NAMESPACE
class QMetaMethod;
QT_END_NAMESPACE

MC_FORWARD_DECLARE_CLASS(McIocBoot)

MC_FORWARD_DECLARE_PRIVATE_DATA(McControllerContainer)

class McControllerContainer : public QObject, public IMcControllerContainer {
	Q_OBJECT

public:
	explicit McControllerContainer(QObject *parent = nullptr);
	~McControllerContainer() override;

    void init(const QSharedPointer<McIocBoot> &boot) noexcept;
    
    QVariant invoke(const QString &uri, const QVariant &body) noexcept override;

private:
    QVariant invoke(const QString &uri) noexcept;
	QVariant invoke(const QString &uri, const QJsonObject &data) noexcept;
    
    bool splitBeanAndFunc(const QString &uri
                          , QSharedPointer<QObject> &bean
                          , QString &func
                          , QJsonObject &errRet) noexcept;
	QVariant invokeForUri(const QSharedPointer<QObject> &bean
                          , const QString &func
                          ,  const QMap<QString, QVariant> &args) noexcept;
	QMap<QString, QVariant> splitParam(const QString &param) noexcept;
	bool isMethodMatching(const QMetaMethod &m, const QList<QString> &argNames) noexcept;
	void removeDuplication(QList<QString> &argNames, QList<QByteArray> &paramNames, QList<QByteArray> &paramTypes) noexcept;
	QVariant invokeForArgs(const QSharedPointer<QObject> &bean
                           , const QMetaMethod &method
                           , const QMap<QString, QVariant> &args) noexcept;
    QVariantList makeValues(const QMetaMethod &method
                            , const QMap<QString, QVariant> &args
                            , int maxParamSize
                            , QVariant *errMsg = nullptr
                            , bool *ok = nullptr) noexcept;
    QVariant makeObjectValue(const QByteArray &typeName, const QVariant &arg) noexcept;
    bool isSharedPointerObject(const QByteArray &typeName, QByteArray &objTypeName) noexcept;

private:
	MC_DECLARE_PRIVATE(McControllerContainer)
};
    
MC_DECLARE_POINTER(McControllerContainer)
