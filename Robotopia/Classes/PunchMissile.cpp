#include "pch.h"
#include "PunchMissile.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "Player.h"
#define SUSTAINMENT_TIME 300 //0.3초동안 미사일 지속됨.

bool PunchMissile::init()
{
	if (!Missile::init())
	{
		return false;
	}

	return true;
}

void PunchMissile::update(float dTime)
{

	auto playerPos = GET_STAGE_MANAGER()->getPlayer()->getPosition();

	if (m_AttackDir == DIR_LEFT)
	{
		setPosition(cocos2d::Point(playerPos.x - m_TargetSize.width, playerPos.y));
	}
	else
	{
		setPosition(cocos2d::Point(playerPos.x + m_TargetSize.width, playerPos.y));
	}
	int nowTime = GET_GAME_MANAGER()->getMicroSecondTime();

	if (nowTime - m_StartTime > SUSTAINMENT_TIME)
	{
		//미사일 완전 삭제
		m_IsDead = true;
		exit();
		removeChild(m_Sprite);
		m_IsUsable = true;
		removeFromParent();
	}
}

void PunchMissile::enter()
{

}

void PunchMissile::exit()
{
	setEnabled(false);
}

void PunchMissile::initMissile()
{
	m_IsDead = false;
	m_IsUsable = true;
}

void PunchMissile::setAttribute(cocos2d::Point pos, Direction attackDir /*= DIR_NONE*/, float damage /*= 0*/, 
								cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/, cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/,
								cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{
	m_Type = OT_MISSILE_PUNCH;
	m_IsDead = false;
	m_IsUsable = false;
	m_IsPlayerMissile = true;
	m_Damage = damage;
	m_AttackDir = attackDir;
	m_TargetSize = contentsSize;
	m_StartTime = GET_GAME_MANAGER()->getMicroSecondTime();
	m_State = MST_KNOCKBACK;
	
	m_Sprite = GET_RESOURCE_MANAGER()->createSprite(ST_PLAYER_ATTACK);
	auto fadeIn = cocos2d::FadeIn::create(SUSTAINMENT_TIME / 4000.f);
	auto delay = cocos2d::DelayTime::create(SUSTAINMENT_TIME / 2000.f);
	auto fadeOut = cocos2d::FadeOut::create(SUSTAINMENT_TIME / 4000.f);
	auto sequence = cocos2d::Sequence::create(fadeIn, delay, fadeOut, nullptr);

	m_Sprite->setAnchorPoint(cocos2d::Point(0.5, 0.5));
	if (m_AttackDir == DIR_LEFT)
	{
		setPosition(cocos2d::Point(pos.x - contentsSize.width, pos.y));
	}
	else
	{
		m_Sprite->setFlippedX(true);
		setPosition(cocos2d::Point(pos.x + contentsSize.width, pos.y));
	}
	addChild(m_Sprite);
	m_Sprite->runAction(sequence);

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(m_Sprite->getContentSize(), meterial);
	m_Body->setContactTestBitmask(PHYC_MONSTER);
	m_Body->setCategoryBitmask(PHYC_MISSILE);
	m_Body->setCollisionBitmask(PHYC_MONSTER);
	m_Body->setTag(static_cast<int>(getType()));
	m_Body->setDynamic(false);
	m_Body->setMass(10);
	m_Body->setRotationEnable(false);
	m_Body->retain();
	setPhysicsBody(m_Body);
}

void PunchMissile::setEnabled(bool enable)
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

bool PunchMissile::onContactBegin(cocos2d::PhysicsContact& contact)
{
	//한 번만 데미지 입히게 하기 위한 용도. 뎀 드가고 나면 그림만 보임.
	//실제 미사일 삭제 시점은 그래픽 사라지는 시점.
	m_IsDead = true;
	return false;
}
