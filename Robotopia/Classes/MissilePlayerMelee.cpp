#include "pch.h"
#include "GameManager.h"
#include "MissilePlayerMelee.h"
#include "ComponentManager.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "DataManager.h"
#include "StageManager.h"


void MissilePlayerMelee::initMissile()
{
	m_IsPlayerMissile = true;
	m_IsUsable = true;
	m_Type = OT_MISSILE_PLAYER_MELEE;
	
	setAnchorPoint(cocos2d::Point::ANCHOR_MIDDLE);

	auto physics = GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(cocos2d::Rect(0, 0, 60, 45), false, 0, 0, 0, PHYC_ALL, PHYC_NONE, PHYC_NONE);
	physics->setEnabled(false);
	
	auto animation = GET_COMPONENT_MANAGER()->createComponent<AnimationComponent>();
	addComponent(animation);
	animation->setAnimation(AT_MISSILE_PLAYER_MELEE, this, 1);

}
	
void MissilePlayerMelee::setAttribute(cocos2d::Point pos, Direction attackDir,
											  float damage, cocos2d::Size contentsSize,
											  cocos2d::Vec2 velocity,
											  cocos2d::Point targetPos)
{
	//setAttribute는 Manager에서 부를 때 한다.
	//즉 이 때가 사용 시점
	m_Velocity = velocity;
	m_Damage = damage;
	m_AttackDir = attackDir;
	m_TargetPos = targetPos;
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

	//여기서 physics를 켜야겠다. 
	auto physicsCompo = static_cast<PhysicsComponent*>(getComponent(CT_PHYSICS));
	physicsCompo->setEnabled(true);
	auto body = physicsCompo->getBody();

	
	auto animationCompo = static_cast<AnimationComponent*>(getComponent(CT_ANIMATION));
	animationCompo->enter();

	m_IsUsable = false;
}

void MissilePlayerMelee::update(float dTime)
{
	
	for (auto& BaseComponent : getChildren())
	{
		BaseComponent->update(dTime);
	}
}

bool MissilePlayerMelee::init()
{
	if (!Missile::init())
	{
		return false;
	}

	return true;
}
void MissilePlayerMelee::enter()
{
}

void MissilePlayerMelee::exit()
{
}