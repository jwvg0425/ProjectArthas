#include "pch.h"
#include "BombMissile.h"
#include "SpriteComponent.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "StageManager.h"
#include "EffectManager.h"
#include "Effect.h"
#include "Player.h"
#include "SoundManager.h"
#define SUSTAINMENT_TIME 300 //0.3초동안 미사일 지속됨.

bool BombMissile::init()
{
	if (!Missile::init())
	{
		return false;
	}

	return true;
}

void BombMissile::update(float dTime)
{
	int nowTime = GET_GAME_MANAGER()->getMicroSecondTime();

	if (!m_IsPhysics)
	{
		setEnabled(false);
		m_IsPhysics = true;
	}

	if (nowTime - m_StartTime > SUSTAINMENT_TIME)
	{
		//미사일 완전 삭제
		m_IsDead = true;
		
	}
}

void BombMissile::enter()
{

}

void BombMissile::exit()
{
	setEnabled(false);
	removeChild(m_Sprite);
	m_IsUsable = true;
	removeFromParent();
}

void BombMissile::initMissile()
{
	m_Type = OT_MISSILE_BOMB;
	m_IsDead = false;
	m_IsUsable = true;
}

void BombMissile::setAttribute(cocos2d::Point pos, Direction attackDir /*= DIR_NONE*/, float damage /*= 0*/, cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/, cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/, cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{
	m_IsDead = false;
	m_IsUsable = false;
	m_IsPlayerMissile = true;
	m_Damage = damage;
	m_AttackDir = attackDir;
	m_TargetSize = contentsSize;
	m_StartTime = GET_GAME_MANAGER()->getMicroSecondTime();
	m_State = MST_KNOCKBACK;
	m_IsPhysics = true;

	m_Sprite = cocos2d::Sprite::create();
	addChild(m_Sprite);
	auto animate = cocos2d::Animate::create(GET_RESOURCE_MANAGER()->createAnimation(AT_GRENADEEXPLOSION));

	m_Sprite->runAction(animate);
	m_Sprite->setScale(6);

	auto meterial = cocos2d::PhysicsMaterial(0, 0, 0);
	m_Body = cocos2d::PhysicsBody::createCircle(96, meterial);
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

bool BombMissile::onContactBegin(cocos2d::PhysicsContact& contact)
{
	//한 번만 데미지 입히게 하기 위한 용도. 뎀 드가고 나면 그림만 보임.
	//실제 미사일 삭제 시점은 그래픽 사라지는 시점.
	m_IsPhysics = false;

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

void BombMissile::setEnabled(bool enable)
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
