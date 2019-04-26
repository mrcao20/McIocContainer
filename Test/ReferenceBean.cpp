#include "ReferenceBean.h"

#include "McContainerGlobal.h"

MC_STATIC(ReferenceBean)
mcRegisterComponent<ReferenceBean *>("ReferenceBean");
mcRegisterListConverter<QList<IHelloWorld *>>();
mcRegisterListConverter<QList<QList<QString>>>();
MC_STATIC_END

ReferenceBean::ReferenceBean(QObject *parent)
	: QObject(parent)
{
}

ReferenceBean::~ReferenceBean() {
}
