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
	 <函数名称>		parseProperty
	 <函数说明>		解析XML文件中的bean属性，并添加到beanDefinition中
	 <参数说明>		propName 属性名
					propEle 包含属性的dom节点
					parsers 解析器，如果需要解析的属性为容器，则需要使用解析器
					value 解析出来的值将放入value中
	 <返回值>		如果本对象无法解析，则返回false，如果由本对象解析则返回true(无论成功与否，如果解析失败，错误信息打印到日志)
	 <作    者>		mrcao
	 <时    间>		2019/4/25
	**************************************************/
    virtual bool parseProperty(const QDomElement &propEle, const QList<QSharedPointer<IMcPropertyParser>>& parsers, QVariant &value) const noexcept = 0;
	/*************************************************
	 <函数名称>		convertProperty
	 <函数说明>		将传入属性值转换为对应属性的属性类型
	 <参数说明>		bean bean
					prop 具体属性
					parsers	解析器，如果需要解析的属性为容器，则需要使用解析器
					refResolver 引用解析器，如果value中包含其他对象，需要使用它来实例化
					value 需要被解析的属性值，直接在value上操作
	 <返回值>		如果本对象无法转换，则返回false，如果由本对象转换则返回true(无论成功与否，如果转换失败，错误信息打印到日志)
	 <作    者>		mrcao
	 <时    间>		2019/4/25
	**************************************************/
    virtual bool convertProperty(const QSharedPointer<QObject>& bean, const char *propTypeName, const QList<QSharedPointer<IMcPropertyParser>>& parsers, IMcBeanReferenceResolver* refResolver, QVariant &value) const noexcept = 0;
};

#define PropertyParserIId "mc.mrcao.interface.IMcPropertyParser/1.0"

Q_DECLARE_INTERFACE(IMcPropertyParser, PropertyParserIId)
