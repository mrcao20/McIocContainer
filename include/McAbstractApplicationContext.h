#ifndef _MC_ABSTRACT_APPLICATION_CONTEXT_H_
#define _MC_ABSTRACT_APPLICATION_CONTEXT_H_

#include "IMcApplicationContext.h"
#include <qobject.h>

struct McAbstractApplicationContextData;

MC_ABSTRACT_CLASS MCIOCCONTAINER_EXPORT McAbstractApplicationContext
	: public QObject
	, MC_IMPLEMENTS IMcApplicationContext {
	Q_OBJECT

public:
	/*	���캯������Ҫһ��configurableBeanFactory���ṩbean�Ĳ�������
		��������ʱ���Զ�����configurableBeanFactory��������Ϊ��ָ��������
	*/
	McAbstractApplicationContext(IMcConfigurableBeanFactory *factory, QObject *parent = 0);
	virtual ~McAbstractApplicationContext();

	/*************************************************
	 <��������>		getBean
	 <����˵��>		����bean�����ƻ�ȡbean�����û�У��򷵻ؿգ������ô�����Ϣ��
					����У����bean��������ȡbeanʵ����
	 <����˵��>		name bean ����
					parent bean�ĸ�����
	 <����ֵ>
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/77
	**************************************************/
	QObject *getBean(const QString &name, QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
        /*************************************************
         <��������>		getBeanToVariant
         <����˵��>		����bean�����ƻ�ȡ����beanʵ����QVariant�����û�У��򷵻���Чֵ�������ô�����Ϣ��
                                        ����У����bean��������ȡ����beanʵ����QVariant��
         <����˵��>		name bean ����
                                        parent bean�ĸ�����
         <����ֵ>
         <��    ��>		mrcao
         <ʱ    ��>		2019/12/18
        **************************************************/
        QVariant getBeanToVariant(const QString &name, QObject *parent = Q_NULLPTR)  Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
	/*************************************************
	 <��������>		containsBean
	 <����˵��>		����������Ƿ���ڸ�bean
	 <����˵��>		name bean����
	 <����ֵ>		true���ڣ�false������
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/7
	**************************************************/
	bool containsBean(const QString &name) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
	/*************************************************
	 <��������>		registerBeanDefinition
	 <����˵��>		ע�� bean����ĳ��󷽷�ʵ�֡�
	 <����˵��>		name bean����
					beandefinition bean����ʵ��
	 <����ֵ>
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/7
	**************************************************/
	void registerBeanDefinition(const QString &name, IMcBeanDefinition *beanDefinition) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
	// ��ȡbean�Ķ��弯��
	QMap<QString, IMcBeanDefinition *> getBeanDefinitions() Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
	QScopedPointer<McAbstractApplicationContextData> d;
};

#endif // !_MC_ABSTRACT_APPLICATION_CONTEXT_H_
