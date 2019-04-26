#include "McBeanGlobal.h"

#include <McPropertyParserPlugins.h>

void mcInitContainer() {
	McPropertyParserPlugins::getInstance()->loadPlugin();
}