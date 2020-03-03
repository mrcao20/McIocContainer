#include "include/BeanFactory/McBeanGlobal.h"

#include "include/PropertyParser/impl/McPropertyParserPlugins.h"
#include "include/ApplicationContext/impl/McAnnotationApplicationContext.h"


namespace Mc {
namespace Ioc {

void mcInitContainer() noexcept {
	McPropertyParserPlugins::getInstance()->loadPlugin();
}

void connect(const QString &beanName
            , const QString &sender
            , const QString &signal
            , const QString &receiver
            , const QString &slot
            , Qt::ConnectionType type) noexcept {
    
    McAnnotationApplicationContext::addConnect(beanName, sender, signal, receiver, slot, type);
}

}
}
