#ifndef _MC_DEFAULT_APPLICATION_CONTEXT_H_
#define _MC_DEFAULT_APPLICATION_CONTEXT_H_

#include "McAbstractApplicationContext.h"

class McDefaultApplicationContext : public McAbstractApplicationContext {
	Q_OBJECT;

public:
	explicit McDefaultApplicationContext(QObject *parent = 0);
	McDefaultApplicationContext(IMcConfigurableBeanFactory *factory, QObject *parent = 0);
	virtual ~McDefaultApplicationContext();
};

#endif // !_MC_DEFAULT_APPLICATION_CONTEXT_H_