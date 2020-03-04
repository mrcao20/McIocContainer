#pragma once

#include <QObject>

#include "include/McMacroGlobal.h"

MC_FORWARD_DECLARE_CLASS(McIocBoot)

MC_FORWARD_DECLARE_PRIVATE_DATA(McModelContainer)

class McModelContainer : public QObject {
	Q_OBJECT

public:
	explicit McModelContainer(QObject *parent = nullptr);
	~McModelContainer() override;

    void init(const QSharedPointer<McIocBoot> &boot) noexcept;

private:
	MC_DECLARE_PRIVATE(McModelContainer)
};
    
MC_DECLARE_POINTER(McModelContainer)
