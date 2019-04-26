/*******************************************************************
 <文件名>		McAbstractBeanDefinitionReader.h
 <详细说明>		抽象类，提供一个发生错误时发射的信号
 <作   者>		mrcao
 <日   期>		2019/4/6
********************************************************************/

#ifndef _MC_ABSTRACT_BEAN_DEFINITION_READER_H_
#define _MC_ABSTRACT_BEAN_DEFINITION_READER_H_

#include <qobject.h>
#include "IMcBeanDefinitionReader.h"

MC_ABSTRACT_CLASS McAbstractBeanDefinitionReader 
	: public QObject
	, MC_IMPLEMENTS IMcBeanDefinitionReader {
	Q_OBJECT;

public:
	explicit McAbstractBeanDefinitionReader(QObject *parent = 0);
	virtual ~McAbstractBeanDefinitionReader();	

};

#endif // !_MC_ABSTRACT_BEAN_DEFINITION_READER_H_