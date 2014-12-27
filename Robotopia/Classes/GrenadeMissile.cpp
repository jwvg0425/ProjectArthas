#include "pch.h"
#include "GrenadeMissile.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "MissileManager.h"
#include "SoundManager.h"
#define PIE 3.1415926538

bool GrenadeMissile::init()
{
	if (!Missile::init())
		return false;

	return true;
}

void GrenadeMissile::update(float dTime)
{

}

void GrenadeMissile::enter()
{

}

void GrenadeMissile::exit()
{
	m_IsDead = true;
}

void GrenadeMissile::dead()
{
	setEnabled(false);
	removeChild(m_Sprite);
	m_IsUsable = true;
	removeFromParent();
}

void GrenadeMissile::initMissile()
{
	m_Type = OT_MISSILE_GRENADE;
	m_IsDead = false;
	m_IsUsable = true;
	m_VelocityValue = 1000; //임시 지정
}

void GrenadeMissile::setAttribute(cocos2d::Point pos, Direction attackDir /*= DIR_NONE*/, float damage /*= 0*/, cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/, cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/, cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{
	m_IsDead = false;
	m_IsUsable = false;
	m_IsPlayerMissile = true;
	m_Damage = damage;
	m_AttackDir = attackDir;
	m_TargetSize = contentsSize;
	m_StartTime = GET_GAME_MANAGER()->getMicroSecondTime();
	m_State = MST_NONE;
	m_ContactNum = 0;

	m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_GRENADE);
	addChild(m_Sprite);

	float distance = pos.getDistance(targetPos);

	float degree = 0;

	if (distance != 0)
	{
		m_Velocity.x = ((targetPos.x - pos.x) / distance) * m_VelocityValue;
		m_Velocity.y = ((targetPos.y - pos.y) / distance) * m_VelocityValue;
		degree = acos((pos.x - targetPos.x) / distance) * 180 / PIE;
	}
	else
	{
		m_Velocity.x = m_VelocityValue;
		m_Velocity.y = 0;
	}

	if (pos.y < targetPos.y)
	{
		m_Sprite->setRotation(degree);
	}
	else
	{
		m_Sprite->setRotation(-degree);
	}

	m_Sprite->setFlippedX(true);

	auto meterial = cocos2d::PhysicsMaterial(1, 0.5, 1);
	m_Body = cocos2d::PhysicsBody::createCircle(16, meterial);
	m_Body->setContactTestBitmask(PHYC_MONSTER | PHYC_BLOCK | PHYC_PLAYER);
	m_Body->setCategoryBitmask(PHYC_MISSILE);
	m_Body->setCollisionBitmask(PHYC_MONSTER | PHYC_BLOCK | PHYC_PLAYER);
	m_Body->setTag(static_cast<int>(getType()));
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->setVelocity(m_Velocity);
	m_Body->retain();
	m_StartPos = pos;
	setPhysicsBody(m_Body);
}

bool GrenadeMissile::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto bodyA = contact.getShapeA()->getBody();
	auto bodyB = contact.getShapeB()->getBody();
	auto componentA = (BaseComponent*)bodyA->getNode();
	auto componentB = (BaseComponent*)bodyB->getNode();
	BaseComponent* enemyComponent;
	bool isComponentA = true;

	if (componentA->getType() == getType())
	{
		enemyComponent = componentB;
		isComponentA = true;
	}
	else
	{
		enemyComponent = componentA;
		isComponentA = false;
	}

	if (enemyComponent->getPhysicsBody()->getCategoryBitmask() == PHYC_BLOCK)
	{
		m_ContactNum++;

		//임시 지정. 정해진 횟수 이상 튕기면 폭발
		if (m_ContactNum >= 3)
		{
			GET_SOUND_MANAGER()->createSound(SoundManager::GREANADE_EXPLOSION, false, getPosition());
			GET_MISSILE_MANAGER()->launchMissile(OT_MISSILE_BOMB, getPosition(), DIR_NONE, cocos2d::Size::ZERO, m_Damage);
			m_IsDead = true;
		}
		return true;
	}

	return false;
}

void GrenadeMissile::setEnabled(bool enable)
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

void GrenadeMissile::setPlayerMissile(bool isPlayers)
{
	m_IsPlayerMissile = isPlayers;
}
