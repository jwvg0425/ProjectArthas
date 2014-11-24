#include "pch.h"
#include "BaseComponent.h"
#include "PhysicsComponent.h"

bool BaseComponent::init()
{
	if( !Node::init() )
	{
		return false;
	}
	m_Type = ComponentType::CT_COMPONENT_START;

	return true;
}

BaseComponent* BaseComponent::getComponent( ComponentType type ) const
{
	_ASSERT( type >= CT_COMPONENT_START && type < CT_COMPONENT_END );
	return ( BaseComponent* )getChildByTag( type );
}

void BaseComponent::removeComponent( BaseComponent* remComponent )
{
	removeChild( remComponent );
}

void BaseComponent::addComponent( BaseComponent* BaseComponent )
{
	int type = BaseComponent->getType();
	addChild(BaseComponent, 0, type);
}

void BaseComponent::removeAllComponent()
{
	removeAllChildren();
}

ComponentType BaseComponent::getType() const
{
	return m_Type;
}

bool BaseComponent::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void BaseComponent::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}

void BaseComponent::setEnabled(bool enable)
{
	auto component = ((PhysicsComponent*)getComponent(CT_PHYSICS));

	if (component != nullptr)
	{
		component->setEnabled(enable);
	}
}



