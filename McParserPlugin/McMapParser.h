#pragma once

#include <QObject>
#include "PropertyParser/IMcPropertyParser.h"

#include <qvector.h>

class McMapParser : public QObject, public IMcPropertyParser {
	Q_OBJECT
	Q_INTERFACES(IMcPropertyParser)

public:
    explicit McMapParser(QObject *parent = nullptr);
    virtual ~McMapParser() override;

    bool parseProperty(const QDomElement &propEle
                       , const QList<QSharedPointer<IMcPropertyParser>> &parsers
                       , QVariant &value) const noexcept override;
    bool convertProperty(const QSharedPointer<QObject>& bean
                         , const char *propTypeName
                         , const QList<QSharedPointer<IMcPropertyParser>>& parsers
                         , IMcBeanReferenceResolver* refResolver
                         , QVariant &value) const noexcept override;

private:
	void getChildTypeName(const QString &parentTypeName
                          , QString &keyTypeName
                          , QString &valueTypeName) const noexcept;

private:
	QVector<QString> m_mapType;
};
