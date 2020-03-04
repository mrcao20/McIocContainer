#include "include/Middleware/Transfer/impl/McModelContainer.h"

#include <QQmlEngine>
#include <QtDebug>

#include "include/McIocBoot.h"
#include "include/ApplicationContext/IMcApplicationContext.h"

MC_DECLARE_PRIVATE_DATA(McModelContainer)
MC_DECLARE_PRIVATE_DATA_END()

McModelContainer::McModelContainer(QObject *parent)
    : QObject(parent)
{
}

McModelContainer::~McModelContainer() {
}

void McModelContainer::init(const QSharedPointer<McIocBoot> &boot) noexcept {
    auto appCtx = boot->getApplicationContext();
	auto beanNames = boot->getComponent(MC_MODEL);
    for (const auto &beanName : beanNames) {
        auto obj = appCtx->getBean(beanName);
        if(!obj) {
            qCritical() << QString("model for named '%1' not exists").arg(beanName);
            continue;
        }
        QQmlEngine::setObjectOwnership(obj.data(), QQmlEngine::CppOwnership);
    }
}
