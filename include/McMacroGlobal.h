#ifndef _MC_MACRO_GLOBAL_H_
#define _MC_MACRO_GLOBAL_H_

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MCIOCCONTAINER_LIB)
#  define MCIOCCONTAINER_EXPORT Q_DECL_EXPORT
# else
#  define MCIOCCONTAINER_EXPORT Q_DECL_IMPORT
# endif
#else
# define MCIOCCONTAINER_EXPORT
#endif

#define MC_SAFE_DELETE(p) (p) ? (delete p, p = Q_NULLPTR) : true

#define MC_INTERFACE class
#define MC_ABSTRACT_CLASS class
#define MC_IMPLEMENTS public

#ifndef Q_MOC_RUN			// 这行语句必须加，只有包围在这行语句之中的宏才能被识别为tag
#define MC_AUTOWIRED		// 用于表示函数是否需要自动注入
#endif // !Q_MOC_RUN

#endif // !_MC_MACRO_GLOBAL_H_

