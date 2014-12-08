#include "pch.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "ComponentManager.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "NPC.h"
#include "DataInfo.h"

bool NPC::init()
{
	if(!BaseComponent::init())
	{
		return false;
	}
	m_Type = OT_NPC_START;
	m_MessageBox = GET_COMPONENT_MANAGER()->createComponent<SpriteComponent>();
	m_MessageBox->initSprite(ST_MESSAGE_BOX, this, cocos2d::Point(0, 60));
	addComponent(m_MessageBox);
	m_MessageBox->exit();
	return true;
}

void NPC::enter()
{
}

void NPC::exit()
{
}

bool NPC::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = (BaseComponent*) bodyA->getNode();
	auto componentB = (BaseComponent*) bodyB->getNode();
	BaseComponent* enemyComponent;
	bool isComponentA = true;

	if(componentA->getType() == getType())
	{
		enemyComponent = componentB;
		isComponentA = true;
	}
	else
	{
		enemyComponent = componentA;
		isComponentA = false;
	}

	if(enemyComponent->getPhysicsBody()->getCategoryBitmask() == PHYC_PLAYER)
	{
		m_OnContact = true;
		m_MessageBox->enter();
	}

	return true;
}

void NPC::onContactSeparate(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = (BaseComponent*) bodyA->getNode();
	auto componentB = (BaseComponent*) bodyB->getNode();
	BaseComponent* enemyComponent;
	bool isComponentA = true;

	if(componentA->getType() == getType())
	{
		enemyComponent = componentB;
		isComponentA = true;
	}
	else
	{
		enemyComponent = componentA;
		isComponentA = false;
	}

	//미사일이랑 충돌 처리
	if(enemyComponent->getPhysicsBody()->getCategoryBitmask() == PHYC_PLAYER)
	{
		m_OnContact = false;
		m_MessageBox->exit();
	}

}

const AllStatus& NPC::getInfo() const
{
	return m_Info;
}



void NPC::bodyInit(cocos2d::Size size)
{
	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(size, meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_PLAYER);
	m_Body->setCategoryBitmask(PHYC_NPC);
	m_Body->setCollisionBitmask(PHYC_PLAYER);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	m_Body->setVelocity(cocos2d::Vec2(0, 0));
	m_Body->setDynamic(true);
	m_Body->retain();
	setPhysicsBody(m_Body);
}

