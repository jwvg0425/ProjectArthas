#include "pch.h"
#include "StateChangeTrigger.h"
#include "StateComponent.h"


void StateChangeTrigger::initChangingStates(ComponentType prevType, ComponentType afterType)
{
	m_PrevType = prevType;
	m_AfterType = afterType;
}

StateChangeTrigger::StateChangeTrigger()
{
	m_Type = TT_STATE_CHANGE;
	m_PrevType = CT_NONE;
	m_AfterType = CT_NONE;
}

StateChangeTrigger::~StateChangeTrigger()
{
}

bool StateChangeTrigger::operator==( const Trigger& trigger )
{
	if (!isEqualTypeTrigger(trigger))
	{
		return false;
	}

	StateChangeTrigger& enemy = (StateChangeTrigger&) trigger;

	int myPrev = m_PrevType;
	int myAfter = m_AfterType;
	int enemyPrev = enemy.m_PrevType;
	int enemyAfter = enemy.m_AfterType;

	//null인 경우 해당 조건은 무시. 따라서 해당 조건은 상대 타입과 같다고 가정한다.
	if (myPrev == CT_NONE)
		myPrev = enemyPrev;
	if (myAfter == CT_NONE)
		myAfter = enemyAfter;

	return (myPrev == enemyPrev) && (myAfter == enemyAfter);
}

