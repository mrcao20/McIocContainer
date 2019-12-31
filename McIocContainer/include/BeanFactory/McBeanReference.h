/*******************************************************************
 <文件名>		McBeanReference.h
 <详细说明>		用于存放bean的引用的相关数据
 <作   者>		mrcao
 <日   期>		2019/4/3
********************************************************************/

#pragma once

#include <qobject.h>
#include "../McMacroGlobal.h"

class MCIOCCONTAINER_EXPORT McBeanReference : public QObject {
    Q_OBJECT

public:
    // 构造器， 必须包含一个bean名称
    explicit McBeanReference(const QString &name, QObject *parent = nullptr)
        : QObject(parent)
        , m_name(name){}
    virtual ~McBeanReference() = default;

    QString getName() { return m_name; }
    void setName(const QString &name) { m_name = name; }

private:
    QString m_name;						// 被引用bean的名称
};

Q_DECLARE_METATYPE(McBeanReference*)
