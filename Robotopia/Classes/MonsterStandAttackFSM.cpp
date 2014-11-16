#include "pch.h"
#include "MonsterStandAttackFSM.h"
#include "GameManager.h"
#include "TriggerManager.h"
#include "StateChangeTrigger.h"
#include "ComponentManager.h"
#include "AttackState.h"
#include "IdleState.h"
#include "StateChangeTrigger.h"

bool Arthas::MonsterStandAttackFSM::init()
{
	if (!FSMComponent::init())
	{
		return false;
	}

	return true;
}


void Arthas::MonsterStandAttackFSM::initFSM()
{
	//여기 수정
	m_Type = FSMT_START;
	
	IdleState* idle = GET_COMPONENT_MANAGER()->createComponent<IdleState>();
	AttackState* attack = GET_COMPONENT_MANAGER()->createComponent<AttackState>();
	addComponent(idle);
	addComponent(attack);
	
	StateChangeTrigger* idleToAttack = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idleToAttack->initChangingStates(STAT_IDLE, STAT_ATTACK);

	StateChangeTrigger* idleToIdle = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idleToIdle->initChangingStates(STAT_IDLE, STAT_IDLE);

	StateChangeTrigger* attackToIdle = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	attackToIdle->initChangingStates(STAT_ATTACK, STAT_IDLE);

	StateChangeTrigger* attackToAttack = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	attackToAttack->initChangingStates(STAT_ATTACK, STAT_ATTACK);

	idle->addTransition(std::make_pair(idleToAttack, attack));
	idle->addTransition(std::make_pair(idleToIdle, idle));
	
	attack->addTransition(std::make_pair(attackToIdle, idle));
	attack->addTransition(std::make_pair(attackToAttack, attack));
	
	m_NowState = idle;
}


void Arthas::MonsterStandAttackFSM::update(float dTime)
{
}

void Arthas::MonsterStandAttackFSM::enter()
{
}

void Arthas::MonsterStandAttackFSM::exit()
{
}
