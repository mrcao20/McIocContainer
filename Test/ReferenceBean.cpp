#include "ReferenceBean.h"

#include "McContainerGlobal.h"

MC_STATIC(ReferenceBean)
mcRegisterBeanFactory<MC_DECL_TYPELIST(ReferenceBean)>("ReferenceBean");
//mcRegisterComponent<ReferenceBean, IReferenceBean>("ReferenceBean");
//mcRegisterComponent<ReferenceBean, IReferenceBean>("ReferenceBean", "aaa", false);
//mcRegisterQVariantListConverter<QList<QVariant>>();
mcRegisterQVariantListConverter<QList<QList<QString>>>();
MC_STATIC_END

ReferenceBean::ReferenceBean(QObject *parent)
	: QObject(parent)
{
}

ReferenceBean::~ReferenceBean() {
}
