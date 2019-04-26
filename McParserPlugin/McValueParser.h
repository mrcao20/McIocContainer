#ifndef _MC_VALUE_PARSER_H_
#define _MC_VALUE_PARSER_H_

#include <QObject>
#include "IMcPropertyParser.h"

class McValueParser : public QObject, public IMcPropertyParser {
	Q_OBJECT
	Q_INTERFACES(IMcPropertyParser)

public:
	explicit McValueParser(QObject *parent = 0);
	virtual ~McValueParser();

	bool parseProperty(const QDomElement &propEle, const QList<IMcPropertyParser *> &parsers, QVariant &value) const noexcept override;
	bool convertProperty(QObject *bean, const char *propTypeName, const QList<IMcPropertyParser *> &parsers, IMcBeanReferenceResolver *refResolver, QVariant &value) const noexcept override;
};

#endif // !_MC_VALUE_PARSER_H_