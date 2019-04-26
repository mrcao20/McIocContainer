#include "McValueParser.h"

#include <qdom.h>
#include <qdebug.h>

#include "IMcBeanDefinition.h"

McValueParser::McValueParser(QObject *parent)
	: QObject(parent)
{
}

McValueParser::~McValueParser(){
}

bool McValueParser::parseProperty(const QDomElement &propEle, const QList<IMcPropertyParser *> &parsers, QVariant &value) const noexcept {
	QDomElement childEle = propEle.firstChildElement("value");
	if (propEle.elementsByTagName("value").size() > 1 || !propEle.hasAttribute("value") && propEle.tagName() != "value" && childEle.isNull())
		return false;		// ������value�������󲻽���

	QString str = "";
	if (propEle.hasAttribute("value"))
		str = propEle.attribute("value");
	else if(propEle.tagName() == "value")
		str = propEle.text();
	else
		str = childEle.text();

	if (!str.isEmpty())
		value = str;
	return true;
}

bool McValueParser::convertProperty(QObject *bean, const char *propTypeName, const QList<IMcPropertyParser *> &parsers, IMcBeanReferenceResolver *refResolver, QVariant &value) const noexcept {
	return false;	// �����󲻽��������ݸ���������������
}