#include "McMapParser.h"

#include <qdom.h>
#include <qregularexpression.h>
#include <qdebug.h>

#include "BeanDefinition/IMcBeanDefinition.h"
#include "McMacroGlobal.h"

McMapParser::McMapParser(QObject *parent)
	: QObject(parent)
{
	m_mapType.append("map");
	m_mapType.append("hash");
}

McMapParser::~McMapParser(){
}

bool McMapParser::parseProperty(
        const QDomElement &propEle
        , const QList<QSharedPointer<IMcPropertyParser>> &parsers
        , QVariant &value) const noexcept {
    
    if(propEle.tagName() != MC_PROPERTY && !m_mapType.contains(propEle.tagName())) {
        return false;       // 此解析器只能解析属性
    }
    QDomNode childNode = propEle.firstChild();
	if (m_mapType.contains(propEle.nodeName()))
		childNode = propEle;
	if (childNode.isNull() || !childNode.isElement() || !m_mapType.contains(childNode.nodeName()))
		return false;		// 不存在list，本对象不解析

    QMap<QVariant, QVariant> map;
	QDomNodeList nodes = childNode.childNodes();
	for (int i = 0; i < nodes.size(); ++i) {
		QDomElement ele = nodes.at(i).toElement();
		if (ele.isNull() || ele.tagName() != "entry")
			continue;
        QVariant mapKey, mapValue;
        if(ele.hasAttribute("key")) {
            mapKey = ele.attribute("key");
        }
        if(ele.hasAttribute("value")) {
            mapValue = ele.attribute("value");
        }
        
        QDomElement entryChildEle = ele.firstChildElement();
        while(!entryChildEle.isNull()) {
            if(entryChildEle.tagName() == "key") {
                auto keyChildEle = entryChildEle.firstChildElement();
                if(keyChildEle.isNull()) {
                    mapKey = entryChildEle.text();
                }else{
                    for (auto parser : parsers) {	// 此处为递归解析，即调用已存在的解析器解析entry内容
                        if (parser->parseProperty(keyChildEle, parsers, mapKey)) {
                            break;
                        }
                    }
                }
            }else if(entryChildEle.tagName() == "value") {
                auto valueChildEle = entryChildEle.firstChildElement();
                if(valueChildEle.isNull()) {
                    mapValue = entryChildEle.text();
                }else{
                    for (auto parser : parsers) {	// 此处为递归解析，即调用已存在的解析器解析entry内容
                        if (parser->parseProperty(valueChildEle, parsers, mapValue)) {
                            break;
                        }
                    }
                }
            }
            
            entryChildEle = entryChildEle.nextSiblingElement();
        }
        
        if(mapKey.isValid() && mapValue.isValid()) {
            map.insert(mapKey, mapValue);
        }
	}

	value.setValue(map);
	return true;
}

bool McMapParser::convertProperty(
        const QSharedPointer<QObject>& bean
        , const char *propTypeName
        , const QList<QSharedPointer<IMcPropertyParser>>& parsers
        , IMcBeanReferenceResolver* refResolver
        , QVariant &value) const noexcept {
    
	// 判断属性值是否是一个QMap
	if (!value.canConvert<QMap<QVariant, QVariant>>())
		return false;	// 本解析器无法解析，传递给其他解析器解析
	// 如果是就将其转换
	QString keyTypeName, valueTypeName;
	getChildTypeName(propTypeName, keyTypeName, valueTypeName);
	auto map = value.value<QMap<QVariant, QVariant>>();
    decltype (map) resultMap;
	value.clear();	// 清空value，使其无效
    QMapIterator<decltype (map)::key_type, decltype (map)::mapped_type> i(map);
    while(i.hasNext()) {
        auto item = i.next();
        auto key = item.key();
        auto value = item.value();
        for (auto parser : parsers) {	// 递归，使用所有解析器循环解析
			if (parser->convertProperty(bean, keyTypeName.toLocal8Bit().data(), parsers, refResolver, key))
				break;
		}
        for (auto parser : parsers) {	// 递归，使用所有解析器循环解析
			if (parser->convertProperty(bean, valueTypeName.toLocal8Bit().data(), parsers, refResolver, value))
				break;
		}
        if(key.isValid() && value.isValid()) {
            resultMap.insert(key, value);
        }
    }
	value.setValue(resultMap);	// 将转换完成的map再传回去
	return true;
}

void McMapParser::getChildTypeName(const QString &parentTypeName
                                   , QString &keyTypeName
                                   , QString &valueTypeName) const noexcept {
    
    if(parentTypeName == "QVariantMap") {
        keyTypeName = "QString";
        valueTypeName = "QVariant";
        return;
    }
	QRegularExpression re(R"(.+\<(.+),(.+)\>)");
	QRegularExpressionMatch match = re.match(parentTypeName);
	Q_ASSERT(match.capturedTexts().size() == 3);
	keyTypeName = match.capturedTexts().at(1).simplified();
    valueTypeName = match.capturedTexts().at(2).simplified();
}
