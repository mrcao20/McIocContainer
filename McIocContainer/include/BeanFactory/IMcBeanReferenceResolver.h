/*******************************************************************
 <�ļ���>		IMcBeanReferenceResolver.h
 <��ϸ˵��>		��Ҫһ��beanReferenceResolver �������beanReference��һЩ��Ϊ 
				�������beanReference����ʵ������
 <��   ��>		mrcao
 <��   ��>		2019/4/3
********************************************************************/

#pragma once

#include "../McMacroGlobal.h"

#include <qobject.h>

class McBeanReference;

MC_INTERFACE IMcBeanReferenceResolver {

public:
	virtual ~IMcBeanReferenceResolver() = default;

	/*************************************************
	 <��������>		resolveBeanReference
	 <����˵��>		����beanReference����ʵ������
	 <����˵��>		beanRef beanReference
     <����ֵ>        ���ɵ�referenceʵ��
	 <��    ��>		mrcao
	 <ʱ    ��>		2019/4/3
	**************************************************/
    virtual QSharedPointer<QObject> resolveBeanReference(const QSharedPointer<McBeanReference>& beanRef) Q_DECL_NOEXCEPT = 0;
    /*************************************************
     <��������>		resolveBeanReferenceToQVariant
     <����˵��>		����beanReference���ɰ���ʵ�������QVariant��
     <����˵��>		beanRef beanReference
     <����ֵ>        ���ɰ���referenceʵ����QVariant
                    ע��QVariant�а���������ΪQSharedPointer<McBeanReference::getName()>������ײ�����
     <��    ��>		mrcao
     <ʱ    ��>		2019/12/22
    **************************************************/
    virtual QVariant resolveBeanReferenceToQVariant(const QSharedPointer<McBeanReference>& beanRef) Q_DECL_NOEXCEPT = 0;
};
