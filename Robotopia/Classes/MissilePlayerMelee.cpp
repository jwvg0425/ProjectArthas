#include "pch.h"
#include "GameManager.h"
#include "PhysicsComponent.h"
#include "MissilePlayerMelee.h"
#include "ComponentManager.h"
#include "ObserverComponent.h"
#include "TriggerManager.h"
#include "PhysicsTrigger.h"




void Arthas::MissilePlayerMelee::initMissile()
{
	m_Type = OT_MISSILE_PLAYER_MELEE;
	m_IsPlayerMissile = true;
	m_IsUsable = true;
	m_Velocity = { 0, 0 };

	auto physics = GET_COMPONENT_MANAGER()->createComponent<PhysicsComponent>();
	addComponent(physics);
	physics->initPhysics(cocos2d::Rect(0, 0, 65, 50), true, 0, 0, 0, PHYC_ALL, PHYC_ALL, PHYC_ALL);
	//일단 물리 body 끄고 '부를 때 켜준다.' 
	physics->setEnabled(false);
	//여기서 누구랑 부딪히지 않을지 정해줄 수 있구나. 
	//physics->addIgnoreCollision(OT_FLOOR, DIR_UP);
	auto observer = GET_COMPONENT_MANAGER()->createComponent<ObserverComponent>();
	addComponent(observer);

	m_PhysicsTirgger = GET_TRIGGER_MANAGER()->createTrigger<PhysicsTrigger>();


}
	
void Arthas::MissilePlayerMelee::setAttribute(cocos2d::Point pos, Direction attackDir,
											  float damage, cocos2d::Vec2 velocity)
{
	//setAttribute는 Manager에서 부를 때 한다. 
	m_Velocity = velocity;
	m_Damage = damage;
	m_AttackDir = attackDir;
	setPosition(pos);
	
	//여기서 physics를 켜야겠다. 
	auto physicsCompo = (PhysicsComponent*)getComponent(CT_PHYSICS);
	physicsCompo->setEnabled(true);
	

	//언제다시 true로 바꿀 것이냐
	//이게 사라지면 true로 바꿔야 되는데
	m_IsUsable = false;
}

void Arthas::MissilePlayerMelee::update(float dTime)
{
	for (auto& component : getChildren())
	{
		component->update(dTime);
	}
	auto observerCompo = (ObserverComponent*)getComponent(CT_OBSERVER);
	m_Triggers = observerCompo->getTriggers();

	for (auto& tirrger : m_Triggers)
	{
		if (m_PhysicsTirgger == tirrger)
		{
			m_IsUsable = true;
			auto physicsCompo = (PhysicsComponent*)getComponent(CT_PHYSICS);
			physicsCompo->setEnabled(false);
		}
	}

}

bool Arthas::MissilePlayerMelee::init()
{
	if (!Missile::init())
	{
		return false;
	}

	return true;
}
void Arthas::MissilePlayerMelee::enter()
{
}

void Arthas::MissilePlayerMelee::exit()
{
}