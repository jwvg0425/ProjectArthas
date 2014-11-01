#include "StateChangeTrigger.h"
#include "StateComponent.h"


void Arthas::StateChangeTrigger::initChangingStates(StateComponent* prevState, StateComponent* afterState)
{
	m_PrevState = prevState;
	m_AfterState = afterState;
}

Arthas::StateChangeTrigger::StateChangeTrigger()
{
	m_Type = TT_STATE_CHANGE;
	m_PrevState = nullptr;
	m_AfterState = nullptr;
}

Arthas::StateChangeTrigger::~StateChangeTrigger()
{
	if (m_IsAutoRelease)
	{
		SAFE_DELETE(m_PrevState);
		SAFE_DELETE(m_AfterState);
	}
}

bool Arthas::StateChangeTrigger::operator==(Trigger& trigger)
{
	if (!isEqualTypeTrigger(trigger))
	{
		return false;
	}

	Arthas::StateChangeTrigger& enemy = (Arthas::StateChangeTrigger&) trigger;

	int myPrev = (m_PrevState) ? m_PrevState->getType() : -1;
	int myAfter = (m_AfterState) ? m_AfterState->getType() : -1;
	int enemyPrev = (enemy.m_PrevState)? enemy.m_PrevState->getType() : -1;
	int enemyAfter = (enemy.m_AfterState) ? enemy.m_AfterState->getType() : -1;

	//null인 경우 해당 조건은 무시. 따라서 해당 조건은 상대 타입과 같다고 가정한다.
	if (myPrev == -1)
		myPrev = enemyPrev;
	if (myAfter == -1)
		myAfter = enemyAfter;

	return (myPrev == enemyPrev) && (myAfter == enemyAfter);
}

