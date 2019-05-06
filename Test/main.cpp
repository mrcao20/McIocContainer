#include <QtCore/QCoreApplication>

#include "McLogManager.h"
#include "McPropertyConfigurator.h"
#include "McIocContainer.h"
#include "McXmlApplicationContext.h"
#include "ReferenceBean.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	McLog::McPropertyConfigurator::configure("./init.ini");
	McLog::McLogManager::installQtMessageHandler();
	McIocContainer::getInstance()->initContainer();
	IMcApplicationContext *appCtx = new McXmlApplicationContext("./myspring.xml");
	ReferenceBean *f = qobject_cast<ReferenceBean *>(appCtx->getBean("referenceBean"));
	f ? f->say() : true;

	qDebug() << McIocContainer::getInstance()->getComponent("Controller");
	return a.exec();
}
