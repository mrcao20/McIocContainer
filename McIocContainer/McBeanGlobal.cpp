#include "../include/McBeanGlobal.h"

#include "../include/McPropertyParserPlugins.h"

void mcInitContainer() {
	McPropertyParserPlugins::getInstance()->loadPlugin();
}
