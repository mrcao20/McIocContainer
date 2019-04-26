#include "McBeanDefinition.h"

#include "McPropertyValues.h"

McBeanDefinition::McBeanDefinition(QObject *parent) 
	: QObject(parent)
	, m_propertyValues(new McPropertyValues(this))
{
}