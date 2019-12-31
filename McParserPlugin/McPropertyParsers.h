#pragma once

#include <QObject>
#include "PropertyParser/IMcPropertyParserCollection.h"

class McPropertyParsers : public QObject, public IMcPropertyParserCollection {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID PropertyParserCollectionIId)
	Q_INTERFACES(IMcPropertyParserCollection)

public:
    explicit McPropertyParsers(QObject *parent = nullptr);
    virtual ~McPropertyParsers() override;

    QList<QSharedPointer<IMcPropertyParser>> customParsers() const noexcept override;

private:
    QList<QSharedPointer<IMcPropertyParser>> m_parsers;
};
