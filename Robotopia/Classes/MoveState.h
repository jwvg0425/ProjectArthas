/************************************************************************/
/*
	CLASS			: MoveState
	Author			: 남현욱
	역할				: 움직이는 상태에 해당하는 클래스.
	최종 수정일자		: 2014-10-31
	최종 수정자		:
	최종 수정사유		:
	Comment			:
*/
/************************************************************************/

#pragma once
#include "StateComponent.h"
#include "cocos2d.h"

BEGIN_NS_AT

class MoveState : public StateComponent
{
public:
	OVERRIDE bool init();
	OVERRIDE void enter();
	OVERRIDE void exit();
	OVERRIDE void update(int dTime);

private:
	Direction	m_Direction;
	int			m_Speed;
};

END_NS_AT