#include "pch.h"
#include "AttackState.h"
#include "GameManager.h"
#include "MissileManager.h"
#include "TriggerManager.h"
#include "SeizeFireTrigger.h"
#include "ObserverComponent.h"
#include "CommonInfo.h"

bool AttackState::init()
{
	if (!StateComponent::init())
	{
		return false;
	}
	m_IsAttacked = false;
	return true;
}

void AttackState::enter()
{
	m_InitTime = GET_GAME_MANAGER()->getTime();
	m_IsAttacked = false;
}

void AttackState::exit()
{
}

void AttackState::update(float dTime)
{
	long currentDelay = GET_GAME_MANAGER()->getTime().tv_sec - m_InitTime.tv_sec;
	if(currentDelay > m_PreDelay && m_IsAttacked == false)
	{
		m_IsAttacked = true;
		CommonInfo* ci = ( CommonInfo* )(m_Ref->getComponent(IT_COMMON));
		auto info = ci->getInfo();
		GET_MISSILE_MANAGER()->launchMissile(m_MissileType, m_Ref->getPosition(),info.dir, info.size);
		CCLOG("balSSA!");
	}
	else if(currentDelay > m_AfterDelay)
	{
		auto endTrigger = GET_TRIGGER_MANAGER()->createTrigger<SeizeFireTrigger>();
		auto observer = (ObserverComponent*) m_Ref->getComponent(CT_OBSERVER);
		observer->addTrigger(endTrigger);
	}
}



void AttackState::setAttribute(BaseComponent* ref, float preDelay, float afterDelay, 
									   ComponentType missleType, int attackPoint)
{
	m_Ref = ref;
	m_PreDelay = preDelay;
	m_AfterDelay = afterDelay;
	m_MissileType = missleType;
	m_AttackPoint = attackPoint;
}
