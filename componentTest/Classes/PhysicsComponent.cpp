#include "PhysicsComponent.h"
#include "Object.h"

void PhysicsComponent::update(float dTime)
{
}

PhysicsComponent::PhysicsComponent(Object* parent, cocos2d::Rect rect, int tag, bool isDynamic,
								float density /*= 0.0f */, float Restitution /*= 0.0f*/, float Friction /*= 0.0f*/, 
								int ContactTestBitmask /*= 0x00000000*/, int CategoryBitmask /*= 0xffffffff*/, int CollisionBitmask /*= 0xffffffff*/)
{
	auto material = cocos2d::PhysicsMaterial(density, Restitution, Friction);

	m_Type = 1;

	m_Body = cocos2d::PhysicsBody::createBox(rect.size, material);
	m_Body->setContactTestBitmask(ContactTestBitmask);
	m_Body->setCategoryBitmask(CategoryBitmask);
	m_Body->setCollisionBitmask(CollisionBitmask);
	m_Body->setTag(tag);
	m_Body->setDynamic(isDynamic);

	m_Parent = parent;

	parent->setPhysicsBody(m_Body);
}

PhysicsComponent::~PhysicsComponent()
{
	m_Body->removeFromWorld();
}

void PhysicsComponent::enter()
{

}

void PhysicsComponent::exit()
{

}
