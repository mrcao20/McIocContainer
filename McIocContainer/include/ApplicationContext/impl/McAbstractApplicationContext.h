#pragma once

#include "../IMcApplicationContext.h"
#include <qobject.h>

struct McAbstractApplicationContextData;

class IMcConfigurableBeanFactory;

MC_ABSTRACT_CLASS MCIOCCONTAINER_EXPORT McAbstractApplicationContext
	: public QObject
	, MC_IMPLEMENTS IMcApplicationContext {
	Q_OBJECT

public:
    /*	构造函数，需要一个configurableBeanFactory来提供bean的操作功能
            本类析构时会自动析构configurableBeanFactory，故无需为其指定父对象
    */
    McAbstractApplicationContext(const QSharedPointer<IMcConfigurableBeanFactory>& factory, QObject *parent = nullptr);
    virtual ~McAbstractApplicationContext() Q_DECL_OVERRIDE;

    /*************************************************
     <函数名称>		getBean
     <函数说明>		根据bean的名称获取bean，如果没有，则返回空，并设置错误信息，
                                    如果有，则从bean定义对象获取bean实例。
     <参数说明>		name bean 名称
                                    parent bean的父对象
     <返回值>
     <作    者>		mrcao
     <时    间>		2019/4/77
    **************************************************/
    QSharedPointer<QObject> getBean(const QString &name) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
    /*************************************************
     <函数名称>		getBeanToVariant
     <函数说明>		根据bean的名称获取包含bean实例的QVariant，如果没有，则返回无效值，并设置错误信息，
                                    如果有，则从bean定义对象获取包含bean实例的QVariant。
     <参数说明>		name bean 名称
                                    parent bean的父对象
     <返回值>
     <作    者>		mrcao
     <时    间>		2019/12/18
    **************************************************/
    QVariant getBeanToVariant(const QString &name)  Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;
    /*************************************************
     <函数名称>		containsBean
     <函数说明>		检测容器中是否存在该bean
     <参数说明>		name bean名称
     <返回值>		true存在，false不存在
     <作    者>		mrcao
     <时    间>		2019/4/7
    **************************************************/
    bool containsBean(const QString &name) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
    QScopedPointer<McAbstractApplicationContextData> d;
};
