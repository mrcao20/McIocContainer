#include "McListParser.h"

#include <qdom.h>
#include <qregularexpression.h>
#include <qdebug.h>

#include "BeanDefinition/IMcBeanDefinition.h"

McListParser::McListParser(QObject *parent)
	: QObject(parent)
{
	m_listType.append("list");
	m_listType.append("vector");
	m_listType.append("set");
}

McListParser::~McListParser(){
}

bool McListParser::parseProperty(const QDomElement &propEle, const QList<QSharedPointer<IMcPropertyParser>> &parsers, QVariant &value) const noexcept {
	QDomNode childNode = propEle.firstChild();
	if (m_listType.contains(propEle.nodeName()))
		childNode = propEle;
	if (childNode.isNull() || !childNode.isElement() || !m_listType.contains(childNode.nodeName()))
		return false;		// ������list�������󲻽���

	QVariantList list;
	QDomNodeList nodes = childNode.childNodes();
	for (int i = 0; i < nodes.size(); ++i) {
		QDomElement ele = nodes.at(i).toElement();
		if (ele.isNull())
			continue;
		QVariant listValue;
		for (auto parser : parsers) {	// �˴�Ϊ�ݹ�������������Ѵ��ڵĽ���������list����
			if (parser->parseProperty(ele, parsers, listValue)) {
				if (listValue.isValid())
					list << listValue;
				break;
			}
		}
	}

	value = list;
	return true;
}

bool McListParser::convertProperty(const QSharedPointer<QObject>& bean, const char *propTypeName, const QList<QSharedPointer<IMcPropertyParser>>& parsers, IMcBeanReferenceResolver* refResolver, QVariant &value) const noexcept {
	// �ж�����ֵ�Ƿ���һ��list
	if (!value.canConvert<QVariantList>())
		return false;	// ���������޷����������ݸ���������������
	// ����Ǿͽ���ת��
	QString childTypeName;
	getChildTypeName(propTypeName, childTypeName);
	auto list = value.value<QVariantList>();
	value.clear();	// ���value��ʹ����Ч
	for (auto &var : list) {	// �˴�����list��QVariant�����ã���ֱ���޸�list�е�ֵ
		for (auto parser : parsers) {	// �ݹ飬ʹ�����н�����ѭ������
			if (parser->convertProperty(bean, childTypeName.toLocal8Bit().data(), parsers, refResolver, var))
				break;
		}
	}
	value = list;	// ��ת����ɵ�list�ٴ���ȥ
	return true;
}

void McListParser::getChildTypeName(const QString &parentTypeName, QString &childTypeName) const noexcept {
    if(parentTypeName == "QVariantList") {
        childTypeName = "QVariant";
        return;
    }
	QRegularExpression re(R"(.+\<(.+)\>)");
	QRegularExpressionMatch match = re.match(parentTypeName);
	Q_ASSERT(match.capturedTexts().size() == 2);
	childTypeName = match.capturedTexts().at(1);
}
