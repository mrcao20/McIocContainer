#pragma once

#include "McAbstractApplicationContext.h"

class McDefaultApplicationContext : public McAbstractApplicationContext {
    Q_OBJECT

public:
    explicit McDefaultApplicationContext(QObject *parent = nullptr);
    McDefaultApplicationContext(const QSharedPointer<IMcConfigurableBeanFactory>& factory, QObject *parent = nullptr);
    virtual ~McDefaultApplicationContext();
};
