#pragma once

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
    McAbstractApplicationContext(const QSharedPointer<IMcConfigurableBeanFactory>& factory, QObject *parent = nullptr);
    virtual ~McAbstractApplicationContext() Q_DECL_OVERRIDE;

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
    QSharedPointer<QObject> getBean(const QString &name) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
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
    QVariant getBeanToVariant(const QString &name)  Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
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
    void registerBeanDefinition(const QString &name, const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
	// ��ȡbean�Ķ��弯��
    QMap<QString, QSharedPointer<IMcBeanDefinition>> getBeanDefinitions() Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
    QScopedPointer<McAbstractApplicationContextData> d;
};
