/*******************************************************************
 <�ļ���>		McDefaultBeanFactory.h
 <��ϸ˵��>		ʵ��beanע��Ļ�������
 <��   ��>		mrcao
 <��   ��>		2019/4/5
********************************************************************/

#pragma once

#include "McAbstractBeanFactory.h"

class McDefaultBeanFactory : public McAbstractBeanFactory {
    Q_OBJECT

public:
    explicit McDefaultBeanFactory(QObject *parent = nullptr);
    virtual ~McDefaultBeanFactory() Q_DECL_OVERRIDE;

protected:
	/*************************************************
	 <��������>		doCreate
	 <����˵��>		����bean ���崴��ʵ���� ����ʵ����Ϊkey�� bean������Ϊvalue��ţ�
					������ addPropertyValue ���� Ϊ������bean�����Խ���ע�롣
	 <����˵��>		name bean ����
	 <����ֵ>		���ش����ɹ���bean����ʧ�ܷ���null
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
        QVariant doCreate(const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
	/*************************************************
	 <��������>		addPropertyValue
	 <����˵��>		����һ��bean�����һ��beanʵ����Ϊ������bean�е�����ע��ʵ����
	 <����˵��>		name bean ����
	 <����ֵ>		�ɹ�����true��������false������¼����
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
        bool addPropertyValue(QObject *bean, const QSharedPointer<IMcBeanDefinition>& beanDefinition) Q_DECL_NOEXCEPT;
};
