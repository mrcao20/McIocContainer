#include "McPropertyParsers.h"

#include "McValueParser.h"
#include "McRefParser.h"
#include "McListParser.h"

McPropertyParsers::McPropertyParsers(QObject *parent)
	: QObject(parent)
{
	m_parsers.append(new McValueParser(this));
	m_parsers.append(new McRefParser(this));
	m_parsers.append(new McListParser(this));
}

McPropertyParsers::~McPropertyParsers(){
}

QList<IMcPropertyParser *> McPropertyParsers::customParsers() const noexcept {
	return m_parsers;
}
