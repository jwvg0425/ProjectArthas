#include "pch.h"
#include "TurretFSM.h"
#include "GameManager.h"
#include "ComponentManager.h"
#include "TriggerManager.h"
#include "IdleState.h"
#include "StateChangeTrigger.h"



bool Arthas::TurretFSM::init()
{
	if (!FSMComponent::init())
	{
		return false;
	}

	return true;
}

void Arthas::TurretFSM::update(float dTime)
{

}

void Arthas::TurretFSM::enter()
{
}

void Arthas::TurretFSM::exit()
{
}

void Arthas::TurretFSM::initTurretFSM()
{
	//Idle State 필요
	//공격 State가 필요
	//

	IdleState* idle = GET_COMPONENT_MANAGER()->createComponent<IdleState>();
	StateChangeTrigger* idleToAttack = GET_TRIGGER_MANAGER()->createTrigger<StateChangeTrigger>();
	idleToAttack->initChangingStates(STAT_IDLE, STAT_ATTACK);
	
	
	
	addComponent(idle);
	//idle->addTransition(std::make_pair(idleToAttack, attack));

}
//
//MoveState* leftMove = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
//leftMove->setAttribute(m_Parent, DIR_LEFT, m_Speed, false);
//
//MoveState* rightMove = GET_COMPONENT_MANAGER()->createComponent<MoveState>();
//rightMove->setAttribute(m_Parent, DIR_RIGHT, m_Speed, false);
//
//PositionTrigger* leftPointTrigger = GET_TRIGGER_MANAGER()->createTrigger<PositionTrigger>();
//leftPointTrigger->initPositionTrigger(m_LeftPoint);
//
//PositionTrigger* rightPointTrigger = GET_TRIGGER_MANAGER()->createTrigger<PositionTrigger>();
//rightPointTrigger->initPositionTrigger(m_RightPoint);
//
//
//addComponent(leftMove);
//leftMove->addTransition(std::make_pair(leftPointTrigger, rightMove));
//addComponent(rightMove);
//rightMove->addTransition(std::make_pair(rightPointTrigger, leftMove));
//
//m_NowState = rightMove;
//
