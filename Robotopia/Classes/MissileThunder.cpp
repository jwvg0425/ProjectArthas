#include "pch.h"
#include "MissileThunder.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Player.h"
#include "StageManager.h"
#include "ComponentManager.h"
#include "AnimationComponent.h"

#define THUNDERWIDHT 20
#define THUNDERHEIGHT 130
#define ARROWREMAINTIME 1000
#define THUNDERREMAINTIME 1000




void MissileThunder::initMissile()
{
	m_IsPlayerMissile = false;
	m_IsUsable = true;
	m_Type = OT_MISSILE_THUNDER;

	setAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE);

	m_ThunderSprite = cocos2d::Sprite::create();
	m_ThunderSprite->retain();
	addChild(m_ThunderSprite);

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	cocos2d::Size thunderSize;
	thunderSize.width = THUNDERWIDHT;
	thunderSize.height = THUNDERHEIGHT;
	m_Body = cocos2d::PhysicsBody::createBox(thunderSize, meterial);
	m_Body->setContactTestBitmask(PHYC_PLAYER);
	m_Body->setCategoryBitmask(PHYC_MISSILE);
	m_Body->setCollisionBitmask(PHYC_PLAYER);
	m_Body->setTag(static_cast<int>(getType()));
	m_Body->setDynamic(false);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->retain();
	setPhysicsBody(m_Body);

	m_ThunderAniComponent = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	m_ThunderAniComponent->setAnimation(AT_MISSILE_THUNDER, this, 1, true);
	addComponent(m_ThunderAniComponent);

}

void MissileThunder::setAttribute(cocos2d::Point pos, Direction attackDir /*= DIR_NONE*/,
								  float damage /*= 0*/, cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/,
								  cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/,
								  cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{

	m_IsExit = false;
	m_IsUsable = false;
	m_ThunderTurn = false;
	m_Damage = damage;
	m_AttackDir = attackDir;
	m_TargetPos = targetPos;
	setPosition(m_TargetPos);
	setEnable(true);
	m_ThunderAniComponent->enter();

}

void MissileThunder::update(float dTime)
{

	if (m_ThunderAniComponent->getAniExit())
	{
		setEnable(false);
		m_IsUsable = true;
		removeFromParent();
	}
	
}

bool MissileThunder::init()
{
	if (!Missile::init())
	{
		return false;
	}

	return true;
}

void MissileThunder::enter()
{
}

void MissileThunder::exit()
{
	setEnable(false);
}

void MissileThunder::setEnable(bool enable)
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
