#include "pch.h"
#include "AttackState.h"
#include "GameManager.h"
#include "TriggerManager.h"
#include "SeizeFireTrigger.h"
#include "ObserverComponent.h"

bool Arthas::AttackState::init()
{
	if (!StateComponent::init())
	{
		return false;
	}
	m_IsAttacked = false;
	return true;
}

void Arthas::AttackState::enter()
{
	m_InitTime = GET_GAME_MANAGER()->getTime();
	m_IsAttacked = false;
}

void Arthas::AttackState::exit()
{
}

void Arthas::AttackState::update(float dTime)
{
	long currentDelay = GET_GAME_MANAGER()->getTime().tv_sec - m_InitTime.tv_sec;
	if(currentDelay > m_PreDelay && m_IsAttacked == false)
	{
		m_IsAttacked = true;
		//¹Ì»çÀÏ ¹ß½Î!!!!!!!!!!!!!!!
		CCLOG("balSSA!");
	}
	else if(currentDelay > m_AfterDelay)
	{
		auto endTrigger = GET_TRIGGER_MANAGER()->createTrigger<SeizeFireTrigger>();
		auto observer = (ObserverComponent*) m_Ref->getComponent(CT_OBSERVER);
		observer->addTrigger(endTrigger);
	}
}



void Arthas::AttackState::setAttribute(Component* ref, float preDelay, float afterDelay, int missleType, int attackPoint)
{
	m_Ref = ref;
	m_PreDelay = preDelay;
	m_AfterDelay = afterDelay;
}
