#include "include/BeanFactory/McBeanGlobal.h"

#include "include/PropertyParser/impl/McPropertyParserPlugins.h"

void mcInitContainer() {
	McPropertyParserPlugins::getInstance()->loadPlugin();
}
