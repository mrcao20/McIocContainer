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
    IMcApplicationContext *appCtx = McIocContainer::getInstance()->getApplicationContext();//new McXmlApplicationContext("qrc:/myspring.xml");
    ReferenceBean *f = qobject_cast<ReferenceBean *>(appCtx->getBean("referenceBean"));
    f != nullptr ? f->say() : void();
    return "aaa";
}
