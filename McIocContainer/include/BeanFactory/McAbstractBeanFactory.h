/*******************************************************************
 <�ļ���>		McAbstractBeanFactory.h
 <��ϸ˵��>		һ�������࣬ ʵ����bean��������ط���
 <��   ��>		mrcao
 <��   ��>		2019/4/3
********************************************************************/

#pragma once

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
    explicit McAbstractBeanFactory(QObject *parent = nullptr);
    virtual ~McAbstractBeanFactory() Q_DECL_OVERRIDE;

    /*************************************************
     <��������>		getBean
     <����˵��>		����bean�����ƻ�ȡbean�����û�У��򷵻ؿգ������ô�����Ϣ��
                        ����У����bean��������ȡbeanʵ����
     <����˵��>		name bean ����
     <����ֵ>
     <��    ��>		mrcao
     <ʱ    ��>		2019/12/22
    **************************************************/
    QSharedPointer<QObject> getBean(const QString &name) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
    /*************************************************
     <��������>		getBeanToVariant
     <����˵��>		����bean�����ƻ�ȡ����beanʵ����QVariant�����û�У��򷵻���Чֵ�������ô�����Ϣ��
                        ����У����bean��������ȡ����beanʵ����QVariant��
     <����˵��>		name bean ����parent bean�ĸ�����
     <����ֵ>
     <��    ��>		mrcao
     <ʱ    ��>		2019/12/2
    **************************************************/
    QVariant getBeanToVariant(const QString &name)  Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
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
    void registerBeanDefinition(const QString &name, const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
    // ��ȡbean�Ķ��弯��
    QMap<QString, QSharedPointer<IMcBeanDefinition>> getBeanDefinitions() Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
    /*************************************************
     <��������>		resolveBeanReference
     <����˵��>		����beanReference����ʵ������
     <����˵��>		beanRef beanReference
     <����ֵ>		���ɵ�referenceʵ��
     <��    ��>		mrcao
     <ʱ    ��>		2019/4/3
    **************************************************/
    QSharedPointer<QObject> resolveBeanReference(const QSharedPointer<McBeanReference>& beanRef) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
    /*************************************************
     <��������>		resolveBeanReferenceToQVariant
     <����˵��>		����beanReference���ɰ���ʵ�������QVariant��
     <����˵��>		beanRef beanReference
     <����ֵ>		���ɰ���referenceʵ����QVariant
                        ע��QVariant�а���������ΪQSharedPointer<McBeanReference::getName()>������ײ�����
     <��    ��>		mrcao
     <ʱ    ��>		2019/12/22
    **************************************************/
    QVariant resolveBeanReferenceToQVariant(const QSharedPointer<McBeanReference>& beanRef) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

protected:
    /*************************************************
     <��������>		doCreate
     <����˵��>		����һ��bean��
     <����˵��>		beanDefinition bean����ʵ��
     <����ֵ>
     <��    ��>		mrcao
     <ʱ    ��>		2019/4/3
    **************************************************/
    virtual QVariant doCreate(const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT = 0;

private:
    QScopedPointer<McAbstractBeanFactoryData> d;	// ���ڴ�����ݣ���cpp��ʵ��
};
