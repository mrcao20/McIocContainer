/*******************************************************************
 <文件名>		McBeanReference.h
 <详细说明>		用于存放bean的引用的相关数据
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#pragma once

#include <qobject.h>
#include "../../McMacroGlobal.h"
#include "../../BeanFactory/McBeanGlobal.h"

class MCIOCCONTAINER_EXPORT McBeanReference : public QObject {
    Q_OBJECT
    MC_DECL_STATIC(McBeanReference)

public:
    // 构造器， 必须包含一个bean名称
    explicit McBeanReference(QObject *parent = nullptr)
        : QObject(parent)
    {}
    virtual ~McBeanReference() = default;
    
    QString getName() const;
    void setName(const QString &name);

    QString getPluginPath() const;
    void setPluginPath(const QString &pluginPath);
    
private:
    QString m_name;						// 被引用bean的名称
    QString m_pluginPath;               // 被引用的插件路径，这个参数和m_name只能有一个存在
};

MC_DECLARE_METATYPE(McBeanReference)
