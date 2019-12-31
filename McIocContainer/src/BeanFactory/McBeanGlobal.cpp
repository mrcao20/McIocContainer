#include "include/BeanFactory/McBeanGlobal.h"

#include "include/PropertyParser/McPropertyParserPlugins.h"

void mcInitContainer() {
	McPropertyParserPlugins::getInstance()->loadPlugin();
}
