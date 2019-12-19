#include "ReferenceBean.h"

#include "McContainerGlobal.h"

MC_STATIC(ReferenceBean)
mcRegisterComponent<ReferenceBean *, IReferenceBean*>("ReferenceBean");
//mcRegisterQVariantListConverter<QList<QVariant>>();
mcRegisterQVariantListConverter<QList<QList<QString>>>();
MC_STATIC_END

ReferenceBean::ReferenceBean(QObject *parent)
	: QObject(parent)
{
}

ReferenceBean::~ReferenceBean() {
}
