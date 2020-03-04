#include "McPropertyParsers.h"

#include "McValueParser.h"
#include "McRefParser.h"
#include "McListParser.h"
#include "McMapParser.h"

McPropertyParsers::McPropertyParsers(QObject *parent)
	: QObject(parent)
{
    m_parsers.append(QSharedPointer<McValueParser>::create());
    m_parsers.append(QSharedPointer<McRefParser>::create());
    m_parsers.append(QSharedPointer<McListParser>::create());
    m_parsers.append(QSharedPointer<McMapParser>::create());
}

McPropertyParsers::~McPropertyParsers(){
}

QList<QSharedPointer<IMcPropertyParser>> McPropertyParsers::customParsers() const noexcept {
	return m_parsers;
}
