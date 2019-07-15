/*******************************************************************
 <�ļ���>		McDefaultBeanFactory.h
 <��ϸ˵��>		ʵ��beanע��Ļ�������
 <��   ��>		mrcao
 <��   ��>		2019/4/5
********************************************************************/

#ifndef _MC_DEFAULT_BEAN_FACTORY_H_
#define _MC_DEFAULT_BEAN_FACTORY_H_

#include "McAbstractBeanFactory.h"

class McDefaultBeanFactory : public McAbstractBeanFactory {
    Q_OBJECT

public:
	explicit McDefaultBeanFactory(QObject *parent = 0);
	virtual ~McDefaultBeanFactory();

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
	QObject *doCreate(IMcBeanDefinition *beanDefinition) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
	/*************************************************
	 <��������>		addPropertyValue
	 <����˵��>		����һ��bean�����һ��beanʵ����Ϊ������bean�е�����ע��ʵ����
	 <����˵��>		name bean ����
	 <����ֵ>		�ɹ�����true��������false������¼����
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
	bool addPropertyValue(QObject *bean, IMcBeanDefinition *beanDefinition) Q_DECL_NOEXCEPT;
};

#endif // !_MC_DEFAULT_BEAN_FACTORY_H_
