#pragma once

#include <QObject>
#include "PropertyParser/IMcPropertyParser.h"

class McRefParser : public QObject, public IMcPropertyParser {
	Q_OBJECT
	Q_INTERFACES(IMcPropertyParser)

public:
    explicit McRefParser(QObject *parent = nullptr);
    virtual ~McRefParser() override;

    bool parseProperty(const QDomElement &propEle, const QList<QSharedPointer<IMcPropertyParser>> &parsers, QVariant &value) const noexcept override;
    bool convertProperty(const QSharedPointer<QObject>& bean, const char *propTypeName, const QList<QSharedPointer<IMcPropertyParser>>& parsers, IMcBeanReferenceResolver* refResolver, QVariant &value) const noexcept override;
};
