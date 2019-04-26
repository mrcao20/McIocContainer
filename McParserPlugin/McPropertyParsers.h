#ifndef _MC_PROPERTY_PARSERS_H_
#define _MC_PROPERTY_PARSERS_H_

#include <QObject>
#include "IMcPropertyParserCollection.h"

class McPropertyParsers : public QObject, public IMcPropertyParserCollection {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID PropertyParserCollectionIId)
	Q_INTERFACES(IMcPropertyParserCollection)

public:
	explicit McPropertyParsers(QObject *parent = 0);
	virtual ~McPropertyParsers();

	QList<IMcPropertyParser *> customParsers() const noexcept override;

private:
	QList<IMcPropertyParser *> m_parsers;
};

#endif // !_MC_PROPERTY_PARSERS_H_