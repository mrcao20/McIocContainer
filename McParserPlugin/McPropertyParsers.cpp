#include "McPropertyParsers.h"

#include "McValueParser.h"
#include "McRefParser.h"
#include "McListParser.h"

McPropertyParsers::McPropertyParsers(QObject *parent)
	: QObject(parent)
{
    m_parsers.append(QSharedPointer<McValueParser>::create());
    m_parsers.append(QSharedPointer<McRefParser>::create());
    m_parsers.append(QSharedPointer<McListParser>::create());
}

McPropertyParsers::~McPropertyParsers(){
}

QList<QSharedPointer<IMcPropertyParser>> McPropertyParsers::customParsers() const noexcept {
	return m_parsers;
}
