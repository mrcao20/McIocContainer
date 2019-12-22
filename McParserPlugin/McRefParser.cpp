#include "McRefParser.h"

#include <qdom.h>
#include <qdebug.h>
#include <qmetaobject.h>

#include "../include/IMcBeanDefinition.h"
#include "../include/McBeanReference.h"
#include "../include/IMcBeanReferenceResolver.h"

McRefParser::McRefParser(QObject *parent)
	: QObject(parent)
{
}

McRefParser::~McRefParser(){
}

bool McRefParser::parseProperty(const QDomElement &propEle, const QList<QSharedPointer<IMcPropertyParser>>& parsers, QVariant &value) const noexcept {
    Q_UNUSED(parsers)
    QDomElement childEle = propEle.firstChildElement("ref");
    if (propEle.elementsByTagName("ref").size() > 1 || (!propEle.hasAttribute("ref") && propEle.tagName() != "ref" && childEle.isNull()))
		return false;		// ������ref�������󲻽���

	// ����ref����ʼ����
	QString ref = "";
	if (propEle.hasAttribute("ref"))
		ref = propEle.attribute("ref");
	else {
		if (propEle.tagName() == "ref")
			childEle = propEle;
		if (childEle.hasAttribute("bean"))
			ref = childEle.attribute("bean");
		else
			ref = childEle.text();
	}

	if (!ref.isEmpty()) {
		// �����Ϊ�գ��򴴽�һ�� ��bean�����á� ʵ�����������Ϊ���ƣ�ʵ����ʱΪ��
        QSharedPointer<McBeanReference> beanRef = QSharedPointer<McBeanReference>::create(ref);
		value = QVariant::fromValue(beanRef);
	}
	return true;
}

bool McRefParser::convertProperty(const QSharedPointer<QObject>& bean, const char *propTypeName, const QList<QSharedPointer<IMcPropertyParser>>& parsers, IMcBeanReferenceResolver* refResolver, QVariant &value) const noexcept {
    Q_UNUSED(parsers)
    Q_UNUSED(bean)
    // �ж�����ֵ�Ƿ���һ��beanReference
    if (!value.canConvert<QSharedPointer<QObject>>())
		return false;	// ���������޷����������ݸ���������������
    // ����Ǿͽ���ת��
    auto beanReference = value.value<QSharedPointer<McBeanReference>>();
    if (!beanReference) {	// �ж��Ƿ��ܹ��ɹ�ת��
		// ʧ�ܣ���¼������Ϣ
		qCritical() << "cannot inject beanReference";
		return true;
	}
    // ����AbstractBeanFactory��resolveBeanReferenceToQVariant����������bean��ȡʵ�����˴����ǵݹ�
    auto objVar = refResolver->resolveBeanReferenceToQVariant(beanReference);
    if (!objVar.isValid()) {
		// ʧ�ܣ���¼������Ϣ
		qCritical() << "cannot get bean from beanReference";
		return true;
	}
    value = objVar;
	QString oldTypeName = value.typeName();
	// �Ƚ�valueת��Ϊ����ʵ����
//	if (!value.convert(QMetaType::type(obj->metaObject()->className()))) {
//		qCritical() << QString("�޷���%1ת��Ϊ%2���뱣֤����Ϊ�̳й�ϵ��ʹ��mcRegisterBeanFactory<%3, %4>()ע���").arg(
//			oldTypeName, propTypeName, oldTypeName, propTypeName);
//		return true;
//	}
//	oldTypeName = value.typeName();
	if (qstrcmp(value.typeName(), propTypeName) == 0)
		return true;
//#if !defined(Q_NO_TEMPLATE_FRIENDS) && !defined(Q_CC_MSVC)
//	value = QVariant(value.userType(), value.constData());
//#else
//	value.d.is_null = false;
//#endif
//	value.data_ptr().is_null = false;
	// �ٽ�ʵ����ת��Ϊ��������Ҫ�Ľӿ�
    if (qstrcmp("QVariant", propTypeName) != 0 && !value.convert(QMetaType::type(propTypeName)))
        qCritical() << QString("cannot convert %1 to %2. Please make sure they are inheriting or use registered for mcRegisterBeanFactory<%3, %4>()").arg(
			oldTypeName, propTypeName, oldTypeName, propTypeName);
	return true;
}
