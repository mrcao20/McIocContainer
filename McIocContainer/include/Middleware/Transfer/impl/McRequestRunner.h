#pragma once

#include <QRunnable>

#include "../../../McMacroGlobal.h"

MC_FORWARD_DECLARE_PRIVATE_DATA(McRequestRunner)

MC_FORWARD_DECLARE_CLASS(McResponse)
MC_FORWARD_DECLARE_CLASS(IMcControllerContainer)

class McRequestRunner : public QRunnable {
public:
    McRequestRunner();
    ~McRequestRunner() override;

    void setResponse(McResponse *val) noexcept;
    void setControllerContainer(const QSharedPointer<IMcControllerContainer> &val) noexcept;
    void setUri(const QString &uri) noexcept;
    void setBody(const QVariant &body) noexcept;

    void run() override;

private:
    MC_DECLARE_PRIVATE(McRequestRunner)
};

MC_DECLARE_POINTER(McRequestRunner)
    
