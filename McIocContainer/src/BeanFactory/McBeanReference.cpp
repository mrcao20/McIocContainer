#include "include/BeanFactory/impl/McBeanReference.h"

MC_STATIC(McBeanReference)
mcRegisterBeanFactory<McBeanReference>();
MC_STATIC_END()

QString McBeanReference::getName() const {
    return m_name;
}

void McBeanReference::setName(const QString &name) {
    m_name = name;
}

QString McBeanReference::getPluginPath() const {
    return m_pluginPath;
}

void McBeanReference::setPluginPath(const QString &pluginPath) {
    m_pluginPath = pluginPath;
}
