#include "../include/McXmlBeanDefinitionReader.h"

#include <QFile>
#include <qdom.h>
#include <qdebug.h>

#include "../include/IMcBeanDefinitionRegistry.h"
#include "../include/McRootBeanDefinition.h"
#include "../include/McBeanReference.h"
#include "../include/McPropertyParserPlugins.h"
#include "../include/IMcPropertyParser.h"

struct McXmlBeanDefinitionReaderData {
	IMcBeanDefinitionRegistry *registry{ Q_NULLPTR };
	QString location;
};

McXmlBeanDefinitionReader::McXmlBeanDefinitionReader(const QString &location, QObject *parent)
	: McAbstractBeanDefinitionReader(parent)
	, d(new McXmlBeanDefinitionReaderData())
{
	d->location = location;
}

McXmlBeanDefinitionReader::~McXmlBeanDefinitionReader(){
}

void McXmlBeanDefinitionReader::readBeanDefinition(IMcBeanDefinitionRegistry *registry) Q_DECL_NOEXCEPT {
	d->registry = registry;

	QFile file(d->location);
	if (!file.open(QIODevice::ReadOnly)) {
		qCritical() << (d->location + " - " + file.errorString());
		return;
	}
	readBeanDefinition(&file);
	file.close();
}

void McXmlBeanDefinitionReader::readBeanDefinition(QIODevice *source) noexcept {
	QDomDocument doc;
	QString errorMsg;
	int errorLine;
	int errorCol;
	if (!doc.setContent(source, &errorMsg, &errorLine, &errorCol)) {
		qCritical() << QString("File %1 (Line %2, Column %3): %4").arg(d->location).arg(errorLine).arg(errorCol).arg(errorMsg);
		return;
	}
	readBeanDefinition(doc);
}

void McXmlBeanDefinitionReader::readBeanDefinition(const QDomDocument &doc) noexcept {
	QDomElement root = doc.documentElement();
	if (root.isNull()) {
		qCritical() << QString("File: %1 Root element is NULL.").arg(d->location);
		return;
	}
	if (root.tagName() != "beans") {
		qCritical() << QString("File: %1 Root element is not beans.").arg(d->location);
		return;
	}
	readBeanDefinition(root.childNodes());
}

void McXmlBeanDefinitionReader::readBeanDefinition(const QDomNodeList &nodes) noexcept {
	for (int i = 0; i < nodes.size(); ++i) {
		QDomElement ele = nodes.at(i).toElement();
		if (ele.isNull() || ele.tagName() != "bean" || ele.attribute("name").isEmpty() ||
			(ele.attribute("class").isEmpty() && ele.attribute("plugin").isEmpty())) {
			qCritical() << "node name must be 'bean', and it's not only contains attribute 'name' and 'class/plugin' but also this attribute not is able null!!";
			continue;
		}
		// 获取给定元素的 name 属性
		QString name = ele.attribute("name");
		// 创建一个bean定义对象
		IMcBeanDefinition *beanDefinition = new McRootBeanDefinition();
		if (ele.hasAttribute("class"))	// 如果指定的class，则通过class创建对象
			// 设置bean 定义对象的 全限定类名
			beanDefinition->setClassName(ele.attribute("class"));
        else{}	// 如果未指定class，则指定的一定是plugin，则通过插件创建对象
            //;
		readBeanDefinition(ele.childNodes(), beanDefinition);
		// 向注册容器 添加bean名称和bean定义
		d->registry->registerBeanDefinition(name, beanDefinition);
	}
}

void McXmlBeanDefinitionReader::readBeanDefinition(const QDomNodeList &propNodes, IMcBeanDefinition *beanDefinition) noexcept {
	for (int i = 0; i < propNodes.size(); ++i) {
		QDomElement propEle = propNodes.at(i).toElement();
		if (propEle.isNull())
			continue;
		// 获取给定元素的 name 属性
		QString propName = propEle.attribute("name");
		if (propName.isEmpty()) {
			qCritical() << "property name no be able null!!";
			continue;
		}
		const QList<IMcPropertyParser *> &parsers = McPropertyParserPlugins::getInstance()->getParsers();
		QVariant value;
		int j = 0;
        for (j = 0; j < parsers.size(); ++j) {
			if (!parsers.at(j)->parseProperty(propEle, parsers, value))
				continue;
			if(value.isValid())
				beanDefinition->addProperty(propName, value);
			else
				qCritical() << QString("the named '%1' property's value is invalid!!").arg(propName);
			break;
		}
		if(j == parsers.size())
			qCritical() << "Configuration problem: <property> element of property "
			<< propName << " it is not found parser";
	}
}
