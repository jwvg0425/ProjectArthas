/************************************************************************/
/*
CLASS			: StateChangeTrigger
Author			: 남현욱
역할				: 상태가 변경될 때 발생하는 트리거 클래스.
최종 수정일자	: 2014-10-29
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Trigger.h"

BEGIN_NS_AT

class StateComponent;

class StateChangeTrigger : public Trigger
{
public:
	void			initChangingStates(StateComponent* prevState, StateComponent* afterState);
	virtual bool	operator ==(Trigger& trigger);

	StateChangeTrigger();
	~StateChangeTrigger();

private:
	StateComponent* m_PrevState;
	StateComponent* m_AfterState;

};

END_NS_AT