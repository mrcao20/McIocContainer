#pragma once

#include <QObject>

#include "../../McMacroGlobal.h"
#include "../../BeanFactory/McBeanGlobal.h"

class MCIOCCONTAINER_EXPORT McBeanConnector : public QObject {
    Q_OBJECT
    MC_DECL_STATIC(McBeanConnector)
public:
    explicit McBeanConnector(QObject *parent = nullptr)
        : QObject(parent){}
    virtual ~McBeanConnector() = default;

    QString getSender() const;
    void setSender(const QString &sender);
    
    QString getSignal() const;
    void setSignal(const QString &signal);
    
    QString getReceiver() const;
    void setReceiver(const QString &receiver);
    
    QString getSlot() const;
    void setSlot(const QString &slot);
    
    Qt::ConnectionType getType() const;
    void setType(const Qt::ConnectionType &type);
    
private:
    QString m_sender{MC_THIS};                      // 发送方beanName，默认为对象本身
    QString m_signal;                               // 信号名
    QString m_receiver{MC_THIS};                    // 接收方beanName，默认为对象本身
    QString m_slot;                                 // 槽名
    Qt::ConnectionType m_type{Qt::AutoConnection};  // 连接方式，默认为自动连接
};

MC_DECLARE_METATYPE(McBeanConnector)
MC_DECLARE_POINTER(McBeanConnector)
