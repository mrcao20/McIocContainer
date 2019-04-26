#include <QtCore/QCoreApplication>

#include "McLogManager.h"
#include "McPropertyConfigurator.h"
#include "McContainer.h"
#include "McXmlApplicationContext.h"
#include "ReferenceBean.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	McLog::McPropertyConfigurator::configure("./init.ini");
	McLog::McLogManager::installQtMessageHandler();
	McContainer::getInstance()->initContainer();
	IMcApplicationContext *appCtx = new McXmlApplicationContext("./myspring.xml");
	ReferenceBean *f = qobject_cast<ReferenceBean *>(appCtx->getBean("referenceBean"));
	f ? f->say() : true;

	return a.exec();
}
