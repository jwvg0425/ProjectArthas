/************************************************************************/
/*
CLASS			: StateComponent
Author			: 김성연
역할				: State들의 추상 클래스
최종 수정일자		: 2014-10-29
최종 수정자		:
최종 수정사유		:
Comment			: 
*/
/************************************************************************/

#pragma once
#include "BaseComponent.h"
#include "cocos2d.h"



class Trigger;
class StateComponent;

class StateComponent : public BaseComponent
{
public:
	OVERRIDE bool init();
	OVERRIDE void enter();
	OVERRIDE void exit();
	OVERRIDE void update(float dTime);

	void			  addTransition(Transition addTransition);
	void			  removeTransition(Transition remTranstion);
	StateComponent*	  getNextState(Trigger* trigger);

protected:
	std::vector<Transition> m_Transitions;
	BaseComponent*				m_Ref;
};

