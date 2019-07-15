/*******************************************************************
 <文件名>		McXmlBeanDefinitionReader.h
 <详细说明>		解析XML文件，并将其注入registry
 <作   者>		mrcao
 <日   期>		2019/4/6
********************************************************************/

#ifndef _MC_XML_BEAN_DEFINITION_READER_H_
#define _MC_XML_BEAN_DEFINITION_READER_H_

#include "McAbstractBeanDefinitionReader.h"

#include <QXmlStreamReader>

QT_BEGIN_NAMESPACE
class QIODevice;
class QDomDocument;
class QDomNodeList;
QT_END_NAMESPACE

class IMcBeanDefinition;

struct McXmlBeanDefinitionReaderData;

class MCIOCCONTAINER_EXPORT McXmlBeanDefinitionReader : public McAbstractBeanDefinitionReader {
	Q_OBJECT;

public:
	explicit McXmlBeanDefinitionReader(const QString &location, QObject *parent = 0);
	virtual ~McXmlBeanDefinitionReader();

	void readBeanDefinition(IMcBeanDefinitionRegistry *registry) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
	void readBeanDefinition(QIODevice *source) noexcept;
	void readBeanDefinition(const QDomDocument &doc) noexcept;
	void readBeanDefinition(const QDomNodeList &nodes) noexcept;
	void readBeanDefinition(const QDomNodeList &propNodes, IMcBeanDefinition *beanDefinition) noexcept;

private:
	QScopedPointer<McXmlBeanDefinitionReaderData> d;
};

#endif // !_MC_XML_BEAN_DEFINITION_READER_H_