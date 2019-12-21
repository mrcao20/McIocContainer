/*******************************************************************
 <�ļ���>		IMcBeanFactory.h
 <��ϸ˵��>		��Ҫһ��beanFactory ����ioc ������һЩ��Ϊ 
				����������ƻ�ȡbean�� 
				����ע��bean������Ϊbean�����ƣ�bean�Ķ��塣
 <��   ��>		mrcao
 <��   ��>		2019/4/3
********************************************************************/

#pragma once

#include "McMacroGlobal.h"

#include <QObject>
#include <QVariant>

MC_INTERFACE IMcBeanFactory {

public:
	virtual ~IMcBeanFactory() = default;

	/*************************************************
	 <��������>		getBean
	 <����˵��>		����bean�����ƴ������л�ȡbean���󣬴˺������̰߳�ȫ�ġ�
	 <����˵��>		name bean����
	 <����ֵ>		beanʵ����ע�⣺���ڹ�����ʱ�����ܱ����٣�Ϊ��ֹʵ��������beanʧЧ��
					��beanδ���ø����󣬹����ֶ�delete��Ҳ����ָ���ڶ�����������bean�ĸ�����
					ע�⣺�˺������ܷ���null
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
	virtual QObject *getBean(const QString &name, QObject *parent = Q_NULLPTR) Q_DECL_NOEXCEPT = 0;
    /*************************************************
     <��������>		getBeanToVariant
     <����˵��>		����bean�����ƴ������л�ȡbean���󣬴˺������̰߳�ȫ�ġ�
     <����˵��>		name bean����
     <����ֵ>		����beanʵ����QVariant��ע�⣺���ڹ�����ʱ�����ܱ����٣�Ϊ��ֹʵ��������beanʧЧ��
                    ��beanδ���ø����󣬹����ֶ�delete��Ҳ����ָ���ڶ�����������bean�ĸ�����
                    ע�⣺�˺������ܷ�����Ч��QVariant
     <��    ��>		mrcao
     <ʱ    ��>		2019/12/18
    **************************************************/
    virtual QVariant getBeanToVariant(const QString &name, QObject *parent = Q_NULLPTR)  Q_DECL_NOEXCEPT = 0;
	/*************************************************
	 <��������>		containsBean
	 <����˵��>		����������Ƿ���ڸ�bean
	 <����˵��>		name bean����
	 <����ֵ>		true���ڣ�false������
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
	virtual bool containsBean(const QString &name) Q_DECL_NOEXCEPT = 0;
};
