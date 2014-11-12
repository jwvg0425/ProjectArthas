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
	void			initChangingStates(ComponentType prevState, ComponentType afterState);
	virtual bool	operator ==( const Trigger& trigger );

	StateChangeTrigger();
	~StateChangeTrigger();

private:
	ComponentType m_PrevType;
	ComponentType m_AfterType;

};

END_NS_AT