#pragma once

#include <qplugin.h>

QT_BEGIN_NAMESPACE
class QDomElement;
QT_END_NAMESPACE

class IMcBeanDefinition;
class IMcBeanReferenceResolver;

class IMcPropertyParser {
public:
	virtual ~IMcPropertyParser() = default;

	/*************************************************
	 <��������>		parseProperty
	 <����˵��>		����XML�ļ��е�bean���ԣ�����ӵ�beanDefinition��
	 <����˵��>		propName ������
					propEle �������Ե�dom�ڵ�
					parsers �������������Ҫ����������Ϊ����������Ҫʹ�ý�����
					value ����������ֵ������value��
	 <����ֵ>		����������޷��������򷵻�false������ɱ���������򷵻�true(���۳ɹ�����������ʧ�ܣ�������Ϣ��ӡ����־)
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/25
	**************************************************/
	virtual bool parseProperty(const QDomElement &propEle, const QList<IMcPropertyParser *> &parsers, QVariant &value) const noexcept = 0;
	/*************************************************
	 <��������>		convertProperty
	 <����˵��>		����������ֵת��Ϊ��Ӧ���Ե���������
	 <����˵��>		bean bean
					prop ��������
					parsers	�������������Ҫ����������Ϊ����������Ҫʹ�ý�����
					refResolver ���ý����������value�а�������������Ҫʹ������ʵ����
					value ��Ҫ������������ֵ��ֱ����value�ϲ���
	 <����ֵ>		����������޷�ת�����򷵻�false������ɱ�����ת���򷵻�true(���۳ɹ�������ת��ʧ�ܣ�������Ϣ��ӡ����־)
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/25
	**************************************************/
	virtual bool convertProperty(QObject *bean, const char *propTypeName, const QList<IMcPropertyParser *> &parsers, IMcBeanReferenceResolver *refResolver, QVariant &value) const noexcept = 0;
};

#define PropertyParserIId "mc.mrcao.interface.IMcPropertyParser/1.0"

Q_DECLARE_INTERFACE(IMcPropertyParser, PropertyParserIId)
