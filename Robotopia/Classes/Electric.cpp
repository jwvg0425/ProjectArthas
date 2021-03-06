#include "pch.h"
#include "Electric.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "DataManager.h"
#include "AnimationComponent.h"

bool Electric::init()
{
	if(!BaseComponent::init())
	{
		return false;
	}
	auto electricEffect = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	electricEffect->setAnimation(AT_LAND_ELECTRIC, this);
	electricEffect->enter();
	electricEffect->setAnchorPoint(cocos2d::Point::ZERO);
	addComponent(electricEffect);
	scheduleUpdate();

	auto tileSize = GET_DATA_MANAGER()->getTileSize();
	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(tileSize, meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_ALL);
	m_Body->setCategoryBitmask(PHYC_TRAP);
	m_Body->setCollisionBitmask(PHYC_ALL);
	m_Body->setDynamic(false);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	setPhysicsBody(m_Body);
	m_Body->retain();

	m_Animation = static_cast<AnimationComponent*>( getComponent(CT_ANIMATION) );
	m_Animation->retain();
	return true;
}

void Electric::update(float dTime)
{

}

void Electric::enter()
{
	m_Animation->enter();
}

void Electric::exit()
{
	m_Animation->exit();
}

void Electric::setEnabled(bool enable)
{
	if (enable == true)
	{
		setPhysicsBody(m_Body);
	}
	else
	{
		setPhysicsBody(nullptr);
		if (m_Body != nullptr)
		{
			m_Body->removeFromWorld();
		}
	}
}

Electric::Electric()
{

}

Electric::~Electric()
{
	SAFE_RELEASE(m_Body);
}

