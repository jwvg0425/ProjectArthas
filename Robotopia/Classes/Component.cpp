#include "Component.h"

bool Component::init()
{
	if( !Node::init() )
	{
		return false;
	}
	return true;
}

void Component::update( float dTime )
{
	for( auto childIter : getChildren() )
	{
		childIter->update( dTime );
	}
}

Component* Component::getComponent( int type )
{
	return ( Component* )getChildByTag( type );
}

void Component::removeComponent( Component* remComponent )
{
	removeChild( remComponent );
}

void Component::addComponent( Component* component )
{
	int type = component->getType();
	component->setParent( this );
	addChild( component , type );
}

void Component::removeAllComponent()
{
	removeAllChildren();
}


