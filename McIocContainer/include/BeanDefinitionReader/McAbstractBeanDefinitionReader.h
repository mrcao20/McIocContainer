/*******************************************************************
 <文件名>		McAbstractBeanDefinitionReader.h
 <详细说明>		抽象类，提供一个发生错误时发射的信号
 <作   者>		mrcao
 <日   期>		2019/4/6
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
