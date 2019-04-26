/*******************************************************************
 <�ļ���>		McAbstractBeanFactory.h
 <��ϸ˵��>		һ�������࣬ ʵ����bean��������ط���
 <��   ��>		mrcao
 <��   ��>		2019/4/3
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
	 <��������>		getBean
	 <����˵��>		����bean�����ƻ�ȡbean�����û�У��򷵻ؿգ������ô�����Ϣ��
					����У����bean��������ȡbeanʵ����
	 <����˵��>		name bean ����
					parent bean�ĸ�����
	 <����ֵ>
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
	QObject *getBean(const QString &name, QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
	/*************************************************
	 <��������>		containsBean
	 <����˵��>		����������Ƿ���ڸ�bean
	 <����˵��>		name bean����
	 <����ֵ>		true���ڣ�false������
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
	bool containsBean(const QString &name) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
	/*************************************************
	 <��������>		registerBeanDefinition
	 <����˵��>		ע�� bean����ĳ��󷽷�ʵ�֡�
	 <����˵��>		name bean����
					beandefinition bean����ʵ��
	 <����ֵ>
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
	void registerBeanDefinition(const QString &name, IMcBeanDefinition *beanDefinition) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
	/*************************************************
	 <��������>		resolveBeanReference
	 <����˵��>		����beanReference����ʵ������
	 <����˵��>		beanRef beanReference
	 <����ֵ>		���ɵ�referenceʵ��
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
	QObject *resolveBeanReference(McBeanReference *beanRef) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

protected:
	/*************************************************
	 <��������>		doCreate
	 <����˵��>		����һ��bean��
	 <����˵��>		beanDefinition bean����ʵ��
	 <����ֵ>
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
	virtual QObject *doCreate(IMcBeanDefinition *beanDefinition) Q_DECL_NOEXCEPT = 0;

private:
	QScopedPointer<McAbstractBeanFactoryData> d;	// ���ڴ�����ݣ���cpp��ʵ��
};

#endif // !_MC_ABSTRACT_BEAN_FACTORY_H_