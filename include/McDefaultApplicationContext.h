#pragma once

#include "McAbstractApplicationContext.h"

class McDefaultApplicationContext : public McAbstractApplicationContext {
    Q_OBJECT

public:
    explicit McDefaultApplicationContext(QObject *parent = nullptr);
    McDefaultApplicationContext(IMcConfigurableBeanFactory *factory, QObject *parent = nullptr);
	virtual ~McDefaultApplicationContext();
};
