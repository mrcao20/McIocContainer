#pragma once

#include <qplugin.h>

class IMcPropertyParser;

class IMcPropertyParserCollection {
public:
	virtual ~IMcPropertyParserCollection() = default;

    virtual QList<QSharedPointer<IMcPropertyParser>> customParsers() const noexcept = 0;
};

#define PropertyParserCollectionIId "mc.mrcao.interface.IMcPropertyParserCollection/1.0"

Q_DECLARE_INTERFACE(IMcPropertyParserCollection, PropertyParserCollectionIId)
