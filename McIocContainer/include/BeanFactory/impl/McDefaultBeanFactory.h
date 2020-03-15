/*******************************************************************
 <文件名>		McDefaultBeanFactory.h
 <详细说明>		实现bean注入的基本功能
 <作   者>		mrcao
 <日   期>		2019/4/5
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
     <函数名称>		doCreate
     <函数说明>		根据bean 定义创建实例， 并将实例作为key， bean定义作为value存放，
                                    并调用 addPropertyValue 方法 为给定的bean的属性进行注入。
     <参数说明>		name bean 名称
     <返回值>		返回创建成功的bean对象，失败返回null
     <作    者>		mrcao
     <时    间>		2019/4/3
    **************************************************/
    QVariant doCreate(const QSharedPointer<IMcBeanDefinition>& beanDefinition, QThread *thread) Q_DECL_NOEXCEPT Q_DECL_OVERRIDE;

private:
    /*************************************************
     <函数名称>		addPropertyValue
     <函数说明>		给定一个bean定义和一个bean实例，为给定的bean中的属性注入实例。
     <参数说明>		name bean 名称
     <返回值>		成功返回true，出错返回false，并记录错误
     <作    者>		mrcao
     <时    间>		2019/4/3
    **************************************************/
    bool addPropertyValue(const QSharedPointer<QObject> &bean
                          , const QSharedPointer<IMcBeanDefinition> &beanDefinition
                          , QVariantMap &proValues) Q_DECL_NOEXCEPT;
    
    bool addObjectConnect(const QSharedPointer<QObject> &bean
                          , const QSharedPointer<IMcBeanDefinition> &beanDefinition
                          , const QVariantMap &proValues) Q_DECL_NOEXCEPT;
    
    QObject *getPropertyObject(const QSharedPointer<QObject> &bean
                               , const QString &proName
                               , const QVariantMap &proValues) Q_DECL_NOEXCEPT;
};
