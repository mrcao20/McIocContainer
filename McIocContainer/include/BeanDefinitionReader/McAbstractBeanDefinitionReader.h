/*******************************************************************
 <�ļ���>		McAbstractBeanDefinitionReader.h
 <��ϸ˵��>		�����࣬�ṩһ����������ʱ������ź�
 <��   ��>		mrcao
 <��   ��>		2019/4/6
********************************************************************/

#pragma once

#include <qobject.h>
#include "IMcBeanDefinitionReader.h"

MC_ABSTRACT_CLASS McAbstractBeanDefinitionReader 
	: public QObject
	, MC_IMPLEMENTS IMcBeanDefinitionReader {
    Q_OBJECT

public:
    explicit McAbstractBeanDefinitionReader(QObject *parent = nullptr);
	virtual ~McAbstractBeanDefinitionReader();	

};
