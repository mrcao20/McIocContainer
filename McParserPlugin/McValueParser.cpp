#include "McValueParser.h"

#include <qdom.h>
#include <qdebug.h>

McValueParser::McValueParser(QObject *parent)
	: QObject(parent)
{
}

McValueParser::~McValueParser(){
}

bool McValueParser::parseProperty(const QDomElement &propEle, const QList<IMcPropertyParser *> &parsers, QVariant &value) const noexcept {
    Q_UNUSED(parsers);
    QDomElement childEle = propEle.firstChildElement("value");
	if (propEle.elementsByTagName("value").size() > 1 || (!propEle.hasAttribute("value") && propEle.tagName() != "value" && childEle.isNull()))
		return false;		// 不存在value，本对象不解析
	
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
    Q_UNUSED(bean);
    Q_UNUSED(propTypeName);
    Q_UNUSED(parsers);
    Q_UNUSED(refResolver);
    Q_UNUSED(value);
    return false;	// 本对象不解析，传递给其他解析器解析
}
