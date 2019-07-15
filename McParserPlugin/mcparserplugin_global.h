#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MCPARSERPLUGIN_LIB)
#  define MCPARSERPLUGIN_EXPORT Q_DECL_EXPORT
# else
#  define MCPARSERPLUGIN_EXPORT Q_DECL_IMPORT
# endif
#else
# define MCPARSERPLUGIN_EXPORT
#endif
