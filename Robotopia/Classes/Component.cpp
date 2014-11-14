#include "pch.h"
#include "Component.h"

bool Arthas::Component::init()
{
	if( !Node::init() )
	{
		return false;
	}
	m_Type = Arthas::ComponentType::CT_COMPONENT_START;

	return true;
}

Arthas::Component* Arthas::Component::getComponent( ComponentType type )
{
	_ASSERT( type >= CT_COMPONENT_START && type < CT_COMPONENT_END );
	return ( Component* )getChildByTag( type );
}

void Arthas::Component::removeComponent( Component* remComponent )
{
	removeChild( remComponent );
}

void Arthas::Component::addComponent( Component* component )
{
	int type = component->getType();
	addChild(component, 0, type);
}

void Arthas::Component::removeAllComponent()
{
	removeAllChildren();
}

Arthas::ComponentType Arthas::Component::getType() const
{
	return m_Type;
}



