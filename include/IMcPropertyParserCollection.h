#ifndef _I_MC_PROPERTY_PARSER_COLLECTION_H_
#define _I_MC_PROPERTY_PARSER_COLLECTION_H_

#include <qplugin.h>

class IMcPropertyParser;

class IMcPropertyParserCollection {
public:
	virtual ~IMcPropertyParserCollection() = default;

	virtual QList<IMcPropertyParser *> customParsers() const noexcept = 0;
};

#define PropertyParserCollectionIId "mc.mrcao.interface.IMcPropertyParserCollection/1.0"

Q_DECLARE_INTERFACE(IMcPropertyParserCollection, PropertyParserCollectionIId)

#endif // !_I_MC_PROPERTY_PARSER_COLLECTION_H_

