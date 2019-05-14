#include "ReferenceBean.h"

#include "McContainerGlobal.h"

MC_STATIC(ReferenceBean)
mcRegisterComponent<ReferenceBean *>("ReferenceBean");
mcRegisterQVariantListConverter<QList<IHelloWorld *>>();
mcRegisterQVariantListConverter<QList<QList<QString>>>();
MC_STATIC_END

ReferenceBean::ReferenceBean(QObject *parent)
	: QObject(parent)
{
}

ReferenceBean::~ReferenceBean() {
}
