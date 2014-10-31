#include "Component.h"

bool Arthas::Component::init()
{
	if( !Node::init() )
	{
		return false;
	}
	m_Parent = nullptr;
	m_Type = Arthas::ComponentType::CT_COMPONENT_START;

	return true;
}

void Arthas::Component::update( float dTime )
{
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
	component->setParent( this );
	addChild( component , type );
}

void Arthas::Component::removeAllComponent()
{
	removeAllChildren();
}

Arthas::ComponentType Arthas::Component::getType() const
{
	return m_Type;
}

void Arthas::Component::setParent( Component* parent )
{
	m_Parent = parent;
}

Arthas::Component* Arthas::Component::getParent() const
{
	return m_Parent;
}



