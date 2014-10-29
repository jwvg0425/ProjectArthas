#include "Component.h"

bool Arthas::Component::init()
{
	if( !Node::init() )
	{
		return false;
	}
	return true;
}

void Arthas::Component::update( float dTime )
{
	for( auto childIter : getChildren() )
	{
		childIter->update( dTime );
	}
}

Arthas::Component* Arthas::Component::getComponent( int type )
{
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


