#pragma once

#include <QtCore/qglobal.h>
#include <QObject>

#include "BeanFactory/McBeanGlobal.h"

class MacroTest : public QObject
{
    MC_DEFINE_TYPELIST(QObject)
public:
    MacroTest();
};

