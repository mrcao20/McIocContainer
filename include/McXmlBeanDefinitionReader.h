/*******************************************************************
 <文件名>		McXmlBeanDefinitionReader.h
 <详细说明>		解析XML文件，并将其注入registry
 <作   者>		mrcao
 <日   期>		2019/4/6
********************************************************************/

#pragma once

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
    Q_OBJECT

public:
    explicit McXmlBeanDefinitionReader(const QString &location, QObject *parent = nullptr);
    virtual ~McXmlBeanDefinitionReader() Q_DECL_OVERRIDE;

    void readBeanDefinition(IMcBeanDefinitionRegistry *registry) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
    void readBeanDefinition(QIODevice *source) noexcept;
    void readBeanDefinition(const QDomDocument &doc) noexcept;
    void readBeanDefinition(const QDomNodeList &nodes) noexcept;
    void readBeanDefinition(const QDomNodeList &propNodes,const QSharedPointer<IMcBeanDefinition>& beanDefinition) noexcept;

private:
	QScopedPointer<McXmlBeanDefinitionReaderData> d;
};
