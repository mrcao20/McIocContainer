#ifndef _MC_REF_PARSER_H_
#define _MC_REF_PARSER_H_
#pragma execution_character_set("utf-8")

#include <QObject>
#include "IMcPropertyParser.h"

class McRefParser : public QObject, public IMcPropertyParser {
	Q_OBJECT
	Q_INTERFACES(IMcPropertyParser)

public:
	explicit McRefParser(QObject *parent = 0);
	virtual ~McRefParser();

	bool parseProperty(const QDomElement &propEle, const QList<IMcPropertyParser *> &parsers, QVariant &value) const noexcept override;
	bool convertProperty(QObject *bean, const char *propTypeName, const QList<IMcPropertyParser *> &parsers, IMcBeanReferenceResolver *refResolver, QVariant &value) const noexcept override;
};

#endif // !_MC_REF_PARSER_H_