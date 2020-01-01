#pragma once

#include <QtCore/qglobal.h>
#include <QSharedPointer>

#ifndef BUILD_STATIC
# if defined(MCIOCCONTAINER_LIB)
#  define MCIOCCONTAINER_EXPORT Q_DECL_EXPORT
# else
#  define MCIOCCONTAINER_EXPORT Q_DECL_IMPORT
# endif
#else
# define MCIOCCONTAINER_EXPORT
#endif

//#define MC_SAFE_DELETE(p) (p) ? (delete p, p = Q_NULLPTR) : static_cast<decltype(p)>(nullptr)
//#define MC_SAFE_DELETE_QPOINTER(p) (!p.isNull()) ? (p->deleteLater()) : void()

#define MC_DECLARE_POINTER(Class) \
    using Class##Ptr = QSharedPointer<Class>; \
    using Class##ConstPtrRef = const QSharedPointer<Class> &; \

#define MC_INTERFACE class
#define MC_ABSTRACT_CLASS class
#define MC_IMPLEMENTS public

#ifndef Q_MOC_RUN			// ����������ӣ�ֻ�а�Χ���������֮�еĺ���ܱ�ʶ��Ϊtag
#define MC_AUTOWIRED		// ���ڱ�ʾ�����Ƿ���Ҫ�Զ�ע��
#endif // !Q_MOC_RUN
