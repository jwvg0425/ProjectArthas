#include "pch.h"
#include "MissileThunder.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Player.h"
#include "StageManager.h"
#include "ComponentManager.h"
#include "AnimationComponent.h"
#include "DataManager.h"
#include "SoundManager.h"

#define THUNDERWIDHT 20
#define THUNDERHEIGHT 130
#define ARROWREMAINTIME 1000
#define THUNDERREMAINTIME 1000




void MissileThunder::initMissile()
{
	m_IsPlayerMissile = false;
	m_IsUsable = true;
	m_Type = OT_MISSILE_THUNDER;
	m_State = MST_NONE;

	setAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE);

	auto aniInfo = GET_DATA_MANAGER()->getAnimationInfo(AT_MISSILE_THUNDER);
	m_Duration = (aniInfo.m_Delay * aniInfo.m_FrameNum * 1000) / 1.5;

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
	GET_SOUND_MANAGER()->createSound(SoundManager::THUNDER, false);
	m_IsDead = false;
	m_IsUsable = false;
	m_ThunderTurn = false;
	m_Damage = damage;
	m_AttackDir = attackDir;
	m_TargetPos = targetPos;
	setPosition(m_TargetPos);
	setEnabled(true);
	m_ThunderAniComponent->enter();

	m_StartTime = GET_GAME_MANAGER()->getMicroSecondTime();

}

void MissileThunder::update(float dTime)
{

	int nowTime = GET_GAME_MANAGER()->getMicroSecondTime();
	if (nowTime - m_StartTime > m_Duration)
	{
	
		setEnabled(false);
		m_IsUsable = true;
		removeFromParent();
	}
/*
	if (m_ThunderAniComponent->getAniExit())
	{
		setEnable(false);
		m_IsUsable = true;
		removeFromParent();
	}
	*/
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
	setEnabled(false);
}

void MissileThunder::setEnabled(bool enable)
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