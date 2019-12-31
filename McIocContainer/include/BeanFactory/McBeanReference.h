/*******************************************************************
 <�ļ���>		McBeanReference.h
 <��ϸ˵��>		���ڴ��bean�����õ��������
 <��   ��>		mrcao
 <��   ��>		2019/4/3
********************************************************************/

#pragma once

#include <qobject.h>
#include "../McMacroGlobal.h"

class MCIOCCONTAINER_EXPORT McBeanReference : public QObject {
    Q_OBJECT

public:
    // �������� �������һ��bean����
    explicit McBeanReference(const QString &name, QObject *parent = nullptr)
        : QObject(parent)
        , m_name(name){}
    virtual ~McBeanReference() = default;

    QString getName() { return m_name; }
    void setName(const QString &name) { m_name = name; }

private:
    QString m_name;						// ������bean������
};

Q_DECLARE_METATYPE(McBeanReference*)
