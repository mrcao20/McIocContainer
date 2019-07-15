#include "McRefParser.h"

#include <qdom.h>
#include <qdebug.h>
#include <qmetaobject.h>

#include "IMcBeanDefinition.h"
#include "McBeanReference.h"
#include "IMcBeanReferenceResolver.h"

McRefParser::McRefParser(QObject *parent)
	: QObject(parent)
{
}

McRefParser::~McRefParser(){
}

bool McRefParser::parseProperty(const QDomElement &propEle, const QList<IMcPropertyParser *> &parsers, QVariant &value) const noexcept {
    Q_UNUSED(parsers);
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
		McBeanReference *beanRef = new McBeanReference(ref);
		value = QVariant::fromValue(beanRef);
	}
	return true;
}

bool McRefParser::convertProperty(QObject *bean, const char *propTypeName, const QList<IMcPropertyParser *> &parsers, IMcBeanReferenceResolver *refResolver, QVariant &value) const noexcept {
    Q_UNUSED(parsers);
    // �ж�����ֵ�Ƿ���һ��beanReference
	if (!value.canConvert<QObject *>())
		return false;	// ���������޷����������ݸ���������������
	// ����Ǿͽ���ת��
	auto obj = value.value<QObject *>();
	if (!obj->inherits("McBeanReference")) {	// �ڶ����ж���������Ƿ��� BeanReference ����
		// ʧ�ܣ���¼������Ϣ
		qCritical() << "cannot inject beanReference";
		return true;
	}
	// �����Զ���תΪBeanReference������Ϊ��һ���ж���obj�Ƿ�ʵ����McBeanReference���ʴ˴�һ���ɹ�
	auto beanReference = qobject_cast<McBeanReference *>(obj);
	// ���ø����AbstractBeanFactory��resolveBeanReference����������bean��ȡʵ�����˴����ǵݹ�
	obj = refResolver->resolveBeanReference(beanReference);
	if (!obj) {
		// ʧ�ܣ���¼������Ϣ
		qCritical() << "cannot get bean from beanReference";
		return true;
	}
	// ����ע��bean�����ԣ��µõ���bean�ǵ�ǰbean���Ӷ�������������bean�ĸ�����Ϊ��ǰbean
	obj->setParent(bean);
	value = QVariant::fromValue(obj);
	QString oldTypeName = value.typeName();
	// �Ƚ�valueת��Ϊ����ʵ����
	if (!value.convert(QMetaType::type(obj->metaObject()->className()))) {
		qCritical() << QString("�޷���%1ת��Ϊ%2���뱣֤����Ϊ�̳й�ϵ��ʹ��mcRegisterBeanFactory<%3, %4>()ע���").arg(
			oldTypeName, propTypeName, oldTypeName, propTypeName);
		return true;
	}
	oldTypeName = value.typeName();
	if (qstrcmp(value.typeName(), propTypeName) == 0)
		return true;
//#if !defined(Q_NO_TEMPLATE_FRIENDS) && !defined(Q_CC_MSVC)
//	value = QVariant(value.userType(), value.constData());
//#else
//	value.d.is_null = false;
//#endif
	value.data_ptr().is_null = false;
	// �ٽ�ʵ����ת��Ϊ��������Ҫ�Ľӿ�
	if (!value.convert(QMetaType::type(propTypeName)))
		qCritical() << QString("�޷���%1ת��Ϊ%2���뱣֤����Ϊ�̳й�ϵ��ʹ��mcRegisterBeanFactory<%3, %4>()ע���").arg(
			oldTypeName, propTypeName, oldTypeName, propTypeName);
	return true;
}
