#include "a.h"

#include <QPluginLoader>

#include "McIocContainer.h"
#include "McXmlApplicationContext.h"
#include "ReferenceBean.h"

A::A()
{

}

QString A::a(){
    McIocContainer::getInstance()->initContainer();
    IMcApplicationContext *appCtx = new McXmlApplicationContext("/home/twoton/Qtproject/McIocContainer/Test/myspring.xml");
//    ReferenceBean *f = qobject_cast<ReferenceBean *>(appCtx->getBean("referenceBean"));
//    f != nullptr ? f->say() : void();
    QVariant var = appCtx->getBeanToVariant("referenceBean");
    IReferenceBean *f = appCtx->getBeanToVariant("referenceBean").value<IReferenceBean*>();
    qDebug() << f;
    f->say();
    return "aaa";
}
