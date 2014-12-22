#include "pch.h"
#include "HPKit.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "StageManager.h"
#include "Player.h"
#include "ComponentManager.h"
#include "AnimationComponent.h"
#include "SoundManager.h"


#define KIT_WIDTH 50
#define KIT_HEIGHT 50
#define FIRST_VELOCITY_X 20
#define FIRST_VELOCITY_Y 200
#define SECOND_VELOCITY_X 5
#define HEALPOINT 15
#define SECOND_VELOCITY_Y -50
#define DOWN_TIME 500
#define WAITING_TIME 1000


bool HPKit::init()
{
	if (!ItemAbstract::init())
	{
		return false;
	}

	m_Type = OT_HPKIT;
	m_HpAni = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	m_HpAni->setAnimation(AT_ITEM_HPKIT, this);
	m_Size.width = KIT_WIDTH;
	m_Size.height = KIT_HEIGHT;
	m_Velocity.x = FIRST_VELOCITY_X;
	m_Velocity.y = FIRST_VELOCITY_Y;
	m_DownTime = DOWN_TIME;
	m_FirstCheckTime = GET_GAME_MANAGER()->getMicroSecondTime();

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(m_Size, meterial, cocos2d::Point(0, 0));
	m_Body->setContactTestBitmask(PHYC_PLAYER || PHYC_BLOCK);
	m_Body->setCategoryBitmask(PHYC_NPC);
	m_Body->setCollisionBitmask(PHYC_PLAYER || PHYC_BLOCK);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocityLimit(1000);
	setPhysicsBody(m_Body);
	m_Body->setVelocity(m_Velocity);
	m_Body->retain();

	setScale(0.65f);

	m_HpAni->enter();

	return true;
}

void HPKit::update(float dTime)
{	
	int nowTime = GET_GAME_MANAGER()->getMicroSecondTime();

	if (!m_IsGettable && nowTime - m_FirstCheckTime > WAITING_TIME)
	{
		m_IsGettable = true;
	}

	if (nowTime - m_FirstCheckTime > m_DownTime && m_IsFirst)
	{
		m_IsFirst = false;
		m_Velocity.x = SECOND_VELOCITY_X;
		m_Velocity.y = SECOND_VELOCITY_Y;
		m_Body->setVelocity(m_Velocity);
	}

}

void HPKit::enter()
{
}

void HPKit::exit()
{
	removeFromParent();
}

bool HPKit::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = (BaseComponent*)bodyA->getNode();
	auto componentB = (BaseComponent*)bodyB->getNode();
	BaseComponent* enemyComponent;

	if (componentA->getType() == getType())
	{
		enemyComponent = componentB;
	}
	else
	{
		enemyComponent = componentA;
	}


	if (enemyComponent->getType() == OT_BLOCK)
	{
		m_Velocity = cocos2d::Vec2::ZERO;
		m_Body->setVelocity(m_Velocity);
	}
	
	if (enemyComponent->getType() == OT_PLAYER && m_IsGettable)
	{
		GET_SOUND_MANAGER()->createSound(SoundManager::STEAM_GET, false);

		GET_STAGE_MANAGER()->getPlayer()->heal(HEALPOINT);
		m_IsDead = true;
	}
	return true;
}

void HPKit::onContactSeparate(cocos2d::PhysicsContact& contact)
{

}

void HPKit::dead()
{
	exit();
}

