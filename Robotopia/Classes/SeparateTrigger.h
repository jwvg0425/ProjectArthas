/************************************************************************/
/*
CLASS			: SeparateTrigger
Author			: 남현욱
역할				: 두 개의 물체가 물리적 접촉 상태에서 분리됐을 때 발생하는 트리거.
최종 수정일자	: 2014-10-29
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Trigger.h"

BEGIN_NS_AT

class Component;

class SeparateTrigger : public Trigger
{
public:
	void			initSeparatingComponents(Component* componentA, Component* componentB);
	virtual bool	operator ==(Trigger& trigger);

	SeparateTrigger();
	~SeparateTrigger();

private:
	Component* m_ComponentA;
	Component* m_ComponentB;
};

END_NS_AT