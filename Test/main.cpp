#include <QtCore/QCoreApplication>

#include <QTimer>

//#include "McLogManager.h"
//#include "McPropertyConfigurator.h"
#include "McIocContainer.h"
#include "McXmlApplicationContext.h"
#include "ReferenceBean.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

    //McLog::McPropertyConfigurator::configure("./init.ini");
	//McLog::McLogManager::installQtMessageHandler();
	McIocContainer::getInstance()->initContainer();
	IMcApplicationContext *appCtx = new McXmlApplicationContext("./myspring.xml");
	ReferenceBean *f = qobject_cast<ReferenceBean *>(appCtx->getBean("referenceBean"));
    f != nullptr ? f->say() : void();

	qDebug() << McIocContainer::getInstance()->getComponent("Controller");

	/*QTimer::singleShot(1000, []() {
		qApp->exit();
	});*/
	return a.exec();
}
