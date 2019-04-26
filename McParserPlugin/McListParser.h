#ifndef _MC_LIST_PARSER_H_
#define _MC_LIST_PARSER_H_

#include <QObject>
#include "IMcPropertyParser.h"

#include <qvector.h>

class McListParser : public QObject, public IMcPropertyParser {
	Q_OBJECT
	Q_INTERFACES(IMcPropertyParser)

public:
	explicit McListParser(QObject *parent = 0);
	virtual ~McListParser();

	bool parseProperty(const QDomElement &propEle, const QList<IMcPropertyParser *> &parsers, QVariant &value) const noexcept override;
	bool convertProperty(QObject *bean, const char *propTypeName, const QList<IMcPropertyParser *> &parsers, IMcBeanReferenceResolver *refResolver, QVariant &value) const noexcept override;

private:
	void getChildTypeName(const QString &parentTypeName, QString &childTypeName) const noexcept;

private:
	QVector<QString> m_listType;
};

#endif // !_MC_LIST_PARSER_H_