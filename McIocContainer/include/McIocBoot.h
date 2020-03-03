#pragma once

#include <QObject>

#include <functional>

#include "McMacroGlobal.h"

using std::function;

MC_FORWARD_DECLARE_CLASS(IMcApplicationContext)
MC_FORWARD_DECLARE_CLASS(QJSEngine)

MC_FORWARD_DECLARE_PRIVATE_DATA(McIocBoot)

class MCIOCCONTAINER_EXPORT McIocBoot : public QObject {
    Q_OBJECT
public:
    explicit McIocBoot(QObject *parent = nullptr);
    ~McIocBoot() override;
    
    static int run(int argc, char *argv[]
                   , const function<void(QJSEngine *)> &func = [](QJSEngine *){}) noexcept;
    
    void initBoot() noexcept;
    
    QSharedPointer<IMcApplicationContext> getApplicationContext() const noexcept;
    
    // 获取所有组建类型为componentType的bean的名称
    QList<QString> getComponent(const QString &componentType) noexcept;
    // 传入的元对象的组件类型是否为type
    bool isComponentType(const QMetaObject *metaObj, const QString &type) noexcept;
    
private:
    MC_DECLARE_PRIVATE(McIocBoot)
};
    
MC_DECLARE_POINTER(McIocBoot)
