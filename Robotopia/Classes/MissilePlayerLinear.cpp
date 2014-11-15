#include "pch.h"
#include "MissilePlayerLinear.h"
#include "GameManager.h"
#include "DataManager.h"
#include "ComponentManager.h"
#include "ObserverComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "TriggerManager.h"
#include "PhysicsTrigger.h"

#define MISSILELINEARWIDHT 65
#define MISSILELINEARHEIGHT 70
#define LINEARMAXMOVEDISTANCE 1000

void Arthas::MissilePlayerLinear::update(float dTime)
{
	for (auto& component : getChildren())
	{
		component->update(dTime);
	}


	m_CurPos = getPosition();
	m_MovedDistance = sqrt((m_StartPos.x - m_CurPos.x)*(m_StartPos.x - m_CurPos.x) +
						   (m_StartPos.y - m_CurPos.y)*(m_StartPos.y - m_CurPos.y));


	if (m_MovedDistance > LINEARMAXMOVEDISTANCE)
	{
		auto physicsCompo = (PhysicsComponent*)getComponent(CT_PHYSICS);
		physicsCompo->setEnabled(false);
		m_IsUsable = true;
		removeFromParent();
	}

	auto observer = (ObserverComponent*)getComponent(CT_OBSERVER);
	if (observer)
	{
		auto triggers = observer->getTriggers();

		auto monsterContactTrigger = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();
		monsterContactTrigger->initTrigger(OT_MISSILE_PLAYER_LINEAR, OT_MONSTER,
										   DIR_ALL, CTT_CONTACT);

		for (auto& pTrigger : triggers)
		{
			if (*monsterContactTrigger == *pTrigger)
			{
				cocos2d::PhysicsContactData contactData = ((PhysicsTrigger*)pTrigger)->getContactData();
				//���⿡ ȿ���� �ִ´�
			}
		}
	}
	

}


void Arthas::MissilePlayerLinear::initMissile()
{
	m_IsPlayerMissile = true;
	m_IsUsable = true;
	m_Type = OT_MISSILE_PLAYER_LINEAR;

	setAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE);

	auto observer = GET_COMPONENT_MANAGER()->createComponent<ObserverComponent>();
	addComponent(observer);


	auto physics = GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(cocos2d::Rect(0, 0, 60, 45), false, 0, 0, 0, PHYC_ALL, PHYC_NONE, PHYC_NONE);
	physics->setEnabled(false);

	auto animation = GET_COMPONENT_MANAGER()->createComponent<AnimationCompnent>();
	addComponent(animation);
	animation->setAnimation(AT_MISSILE_PLAYER_LINEAR, this);
}

void Arthas::MissilePlayerLinear::setAttribute(cocos2d::Point pos, 
											   Direction attackDir /*= DIR_NONE*/, 
											   float damage /*= 0*/, 
											   cocos2d::Size contentsSize /*= cocos2d::Size::ZERO*/, 
											   cocos2d::Vec2 velocity /*= cocos2d::Point::ZERO*/, 
											   cocos2d::Point targetPos /*= cocos2d::Point::ZERO*/)
{
	m_Velocity = velocity;
	m_Damage = damage;
	m_AttackDir = attackDir;
	m_TargetPos = targetPos;
	m_MovedDistance = 0;
	m_CurPos = cocos2d::Point::ZERO;
	m_IsStartPosCheck = true;

	cocos2d::Point setPos;
	float rotation = 0.f;
	if (attackDir == DIR_LEFT)
	{
		rotation = 180.f;
	}


	setPos.x = pos.x + cos(rotation / 90 * MATH_PIOVER2)*contentsSize.width * 1.5f;
	setPos.y = pos.y + sin(rotation / 90 * MATH_PIOVER2)*contentsSize.height;

	setPosition(setPos);
	setRotation(rotation);
	m_StartPos = setPos;

	//���⼭ physics�� �Ѿ߰ڴ�. 
	auto physicsCompo = (PhysicsComponent*)getComponent(CT_PHYSICS);
	physicsCompo->setEnabled(true);

	auto animationCompo = (AnimationCompnent*)getComponent(CT_ANIMATION);
	animationCompo->enter();

	m_IsUsable = false;
}


bool Arthas::MissilePlayerLinear::init()
{
	if (!Missile::init())
	{
		return false;
	}

	return true;
}
void Arthas::MissilePlayerLinear::enter()
{
}

void Arthas::MissilePlayerLinear::exit()
{
}