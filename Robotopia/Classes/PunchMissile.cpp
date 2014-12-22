#include "pch.h"
#include "PunchMissile.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "Player.h"
#include "EffectManager.h"
#include "Effect.h"
#include "SoundManager.h"
#define PUNCH_WIDTH 30
#define PUNCH_HEIGHT 20

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
	m_Type = OT_MISSILE_PUNCH;
	m_IsDead = false;
	m_IsUsable = true;
}

void PunchMissile::setAttribute(cocos2d::Point pos, Direction attackDir /*= DIR_NONE*/, float damage /*= 0*/, 
								cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/, cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/,
								cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{
	m_IsDead = false;
	m_IsUsable = false;
	m_IsPlayerMissile = true;
	m_Damage = damage;
	m_AttackDir = attackDir;
	m_TargetSize = contentsSize;
	m_StartTime = GET_GAME_MANAGER()->getMicroSecondTime();
	m_State = MST_KNOCKBACK;
	
	m_Sprite = cocos2d::Sprite::create();
	auto animation = GET_RESOURCE_MANAGER()->createAnimation(AT_MISSILE_PUNCH);
	animation->setDelayPerUnit(0.05);
	auto animate = cocos2d::Animate::create(animation);
	auto callfunc = cocos2d::CallFuncN::create(CC_CALLBACK_1(PunchMissile::endAnimation, this));


	m_Sprite->runAction(cocos2d::Sequence::create(animate, callfunc, NULL));
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

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createBox(cocos2d::Size(PUNCH_WIDTH,PUNCH_HEIGHT), meterial);
	m_Body->setContactTestBitmask(PHYC_MONSTER);
	m_Body->setCategoryBitmask(PHYC_MISSILE);
	m_Body->setCollisionBitmask(PHYC_MONSTER);
	m_Body->setTag(static_cast<int>(getType()));
	m_Body->setGravityEnable(false);
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

	//이펙트 생성

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

	GET_SOUND_MANAGER()->createSound(SoundManager::MONSTERHIT, false, getPosition());
	GET_EFFECT_MANAGER()->createEffect(ET_PUNCH_MISSILE, enemyComponent->getPosition())->enter();
	return false;
}

void PunchMissile::endAnimation(cocos2d::Ref* sender)
{
	//미사일 완전 삭제
	m_IsDead = true;
	exit();
	removeChild(m_Sprite);
	m_IsUsable = true;
	removeFromParent();
}
