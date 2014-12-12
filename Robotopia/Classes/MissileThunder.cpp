#include "pch.h"
#include "MissileThunder.h"
#include "GameManager.h"
#include "ResourceManager.h"

#define THUNDERWIDHT 20
#define THUNDERHEIGHT 60
#define ARROWREMAINTIME 1000
#define THUNDERREMAINTIME 1000




void MissileThunder::initMissile()
{
	m_IsPlayerMissile = false;
	m_IsUsable = true;
	m_Type = OT_MISSILE_THUNDER;

	setAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE);

	m_ArrowSprite = cocos2d::Sprite::create();
	m_ArrowSprite->retain();
	m_ThunderSprite = cocos2d::Sprite::create();
	m_ThunderSprite->retain();
	
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

}

void MissileThunder::setAttribute(cocos2d::Point pos, Direction attackDir /*= DIR_NONE*/, 
								  float damage /*= 0*/, cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/,
								  cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/, 
								  cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{
	
	m_IsExit = false;
	m_IsUsable = false;
	m_Damage = damage;
	m_AttackDir = attackDir;
	m_ArrowStartTime = GET_GAME_MANAGER()->getMicroSecondTime();

	//타겟 포즈에 플레이어 포즈가 들어올테니까. 
	m_TargetPos = targetPos;
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_DEVIL_ARROW);
	auto animate = cocos2d::Animate::create(animation);
	auto repeat = cocos2d::RepeatForever::create(animate);

	m_ArrowSprite->setVisible(true);
	m_ArrowSprite->setPosition(m_TargetPos);
	m_ArrowSprite->runAction(repeat);


	
}

void MissileThunder::update(float dTime)
{
	int nowTime = GET_GAME_MANAGER()->getMicroSecondTime();
	if (nowTime - m_ArrowStartTime > ARROWREMAINTIME && m_IsAttacking == false)
	{
		m_IsAttacking = true;
		m_ArrowSpriteEnd = true;
		m_ArrowSprite->setVisible(false);
	}

	if (m_IsAttacking && m_ArrowSpriteEnd)
	{
		m_ArrowSpriteEnd = false;
		m_ThunderStartTime = GET_GAME_MANAGER()->getMicroSecondTime();
		auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_MISSILE_THUNDER);
		auto animate = cocos2d::Animate::create(animation);
		auto repeat = cocos2d::RepeatForever::create(animate);

		m_ThunderSprite->runAction(repeat);
		m_ThunderSprite->setPosition(m_TargetPos);
		m_Body->setPositionOffset(m_TargetPos);
	}

	if (nowTime - m_ThunderStartTime > THUNDERREMAINTIME)
	{
		//미사일 완전 삭제
		exit();
		removeChild(m_ArrowSprite);
		removeChild(m_ThunderSprite);
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
}
