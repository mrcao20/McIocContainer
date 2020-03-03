#include "include/BeanFactory/impl/McBeanConnector.h"

MC_STATIC(McBeanConnector)
mcRegisterBeanFactory<McBeanConnector>();
MC_STATIC_END()

QString McBeanConnector::getSender() const {
    return m_sender;
}

void McBeanConnector::setSender(const QString &sender) {
    m_sender = sender.simplified();
}

QString McBeanConnector::getSignal() const {
    return m_signal;
}

void McBeanConnector::setSignal(const QString &signal) {
    m_signal = QMetaObject::normalizedSignature(signal.toLocal8Bit());
}

QString McBeanConnector::getReceiver() const {
    return m_receiver;
}

void McBeanConnector::setReceiver(const QString &receiver) {
    m_receiver = receiver.simplified();
}

QString McBeanConnector::getSlot() const {
    return m_slot;
}

void McBeanConnector::setSlot(const QString &slot) {
    m_slot = QMetaObject::normalizedSignature(slot.toLocal8Bit());
}

Qt::ConnectionType McBeanConnector::getType() const {
    return m_type;
}

void McBeanConnector::setType(const Qt::ConnectionType &type) {
    m_type = type;
}
