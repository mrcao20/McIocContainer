#include "McListParser.h"

#include <qdom.h>
#include <qregularexpression.h>
#include <QDir>
#include <QLibrary>
#include <QCoreApplication>
#include <qdebug.h>

#include "McMacroGlobal.h"
#include "BeanDefinition/IMcBeanDefinition.h"
#include "BeanFactory/impl/McBeanReference.h"

McListParser::McListParser(QObject *parent)
	: QObject(parent)
{
	m_listType.append("list");
	m_listType.append("vector");
	m_listType.append("set");
}

McListParser::~McListParser(){
}

bool McListParser::parseProperty(
        const QDomElement &propEle
        , const QList<QSharedPointer<IMcPropertyParser>> &parsers
        , QVariant &value) const noexcept {
    
    if(propEle.tagName() != MC_PROPERTY && !m_listType.contains(propEle.tagName())) {
        return false;       // 此解析器只能解析属性
    }
    QDomNode childNode = propEle.firstChild();
	if (m_listType.contains(propEle.nodeName()))
		childNode = propEle;
	if (childNode.isNull() || !childNode.isElement() || !m_listType.contains(childNode.nodeName()))
		return false;		// 不存在list，本对象不解析

	QVariantList list;
    
    auto childEle = childNode.toElement();
    if(childEle.hasAttribute("plugins")) {
        QString pluginsPath = childEle.attribute("plugins").simplified();
        pluginsPath = QDir::toNativeSeparators(pluginsPath);
        if(pluginsPath.startsWith(QString("%1%2").arg(".", QDir::separator()))) {
            pluginsPath = pluginsPath.remove(0, 1);   // 移除最前面的.
            pluginsPath = qApp->applicationDirPath() + pluginsPath;   // 补全为全路径
        }
        list = getList(pluginsPath);
    }
    
	QDomNodeList nodes = childNode.childNodes();
	for (int i = 0; i < nodes.size(); ++i) {
		QDomElement ele = nodes.at(i).toElement();
		if (ele.isNull())
			continue;
		QVariant listValue;
		for (auto parser : parsers) {	// 此处为递归解析，即调用已存在的解析器解析list内容
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
	// 判断属性值是否是一个list
	if (!value.canConvert<QVariantList>())
		return false;	// 本解析器无法解析，传递给其他解析器解析
	// 如果是就将其转换
	QString childTypeName;
	getChildTypeName(propTypeName, childTypeName);
	auto list = value.value<QVariantList>();
	value.clear();	// 清空value，使其无效
	for (auto &var : list) {	// 此处遍历list中QVariant的引用，即直接修改list中的值
		for (auto parser : parsers) {	// 递归，使用所有解析器循环解析
			if (parser->convertProperty(bean, childTypeName.toLocal8Bit().data(), parsers, refResolver, var))
				break;
		}
	}
	value = list;	// 将转换完成的list再传回去
	return true;
}

QVariantList McListParser::getList(const QString &dirPath) const noexcept {
    QVariantList list;
    
    QDir dir(dirPath);
    if(!dir.exists()) {
        qCritical() << dirPath << "not exists";
        return list;
    }
    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files);
    for(auto fileInfo : fileInfoList) {
        QString pluginPath = fileInfo.absoluteFilePath();
        if(!QLibrary::isLibrary(pluginPath)) {
            qCritical() << pluginPath << "not a plugin";
            continue;
        }
        QSharedPointer<McBeanReference> beanRef = QSharedPointer<McBeanReference>::create();
        beanRef->setPluginPath(pluginPath);
		list << QVariant::fromValue(beanRef);
    }
    
    return list;
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
