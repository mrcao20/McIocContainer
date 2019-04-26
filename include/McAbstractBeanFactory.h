/*******************************************************************
 <文件名>		McAbstractBeanFactory.h
 <详细说明>		一个抽象类， 实现了bean操作的相关方法
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#ifndef _MC_ABSTRACT_BEAN_FACTORY_H_
#define _MC_ABSTRACT_BEAN_FACTORY_H_

#include <qobject.h>
#include "IMcConfigurableBeanFactory.h"
#include "IMcBeanReferenceResolver.h"

struct McAbstractBeanFactoryData;

MC_ABSTRACT_CLASS McAbstractBeanFactory 
	: public QObject
	, MC_IMPLEMENTS IMcConfigurableBeanFactory
	, MC_IMPLEMENTS IMcBeanReferenceResolver {
	Q_OBJECT

public:
	explicit McAbstractBeanFactory(QObject *parent = 0);
	virtual ~McAbstractBeanFactory();

	/*************************************************
	 <函数名称>		getBean
	 <函数说明>		根据bean的名称获取bean，如果没有，则返回空，并设置错误信息，
					如果有，则从bean定义对象获取bean实例。
	 <参数说明>		name bean 名称
					parent bean的父对象
	 <返回值>
	 <作    者>		mrcao
	 <时    间>		2019/4/3
	**************************************************/
	QObject *getBean(const QString &name, QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
	/*************************************************
	 <函数名称>		containsBean
	 <函数说明>		检测容器中是否存在该bean
	 <参数说明>		name bean名称
	 <返回值>		true存在，false不存在
	 <作    者>		mrcao
	 <时    间>		2019/4/3
	**************************************************/
	bool containsBean(const QString &name) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
	/*************************************************
	 <函数名称>		registerBeanDefinition
	 <函数说明>		注册 bean定义的抽象方法实现。
	 <参数说明>		name bean名称
					beandefinition bean定义实例
	 <返回值>
	 <作    者>		mrcao
	 <时    间>		2019/4/3
	**************************************************/
	void registerBeanDefinition(const QString &name, IMcBeanDefinition *beanDefinition) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
	/*************************************************
	 <函数名称>		resolveBeanReference
	 <函数说明>		根据beanReference生成实例对象。
	 <参数说明>		beanRef beanReference
	 <返回值>		生成的reference实例
	 <作    者>		mrcao
	 <时    间>		2019/4/3
	**************************************************/
	QObject *resolveBeanReference(McBeanReference *beanRef) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

protected:
	/*************************************************
	 <函数名称>		doCreate
	 <函数说明>		创建一个bean。
	 <参数说明>		beanDefinition bean定义实例
	 <返回值>
	 <作    者>		mrcao
	 <时    间>		2019/4/3
	**************************************************/
	virtual QObject *doCreate(IMcBeanDefinition *beanDefinition) Q_DECL_NOEXCEPT = 0;

private:
	QScopedPointer<McAbstractBeanFactoryData> d;	// 用于存放数据，在cpp中实现
};

#endif // !_MC_ABSTRACT_BEAN_FACTORY_H_