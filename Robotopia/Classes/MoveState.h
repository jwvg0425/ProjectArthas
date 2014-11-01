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
	OVERRIDE bool	init();
	OVERRIDE void	enter();
	OVERRIDE void	exit();
	OVERRIDE void	update(float dTime);

	//Physical Component와 같이 동작하면 isPhysical = true, 별도 동작이면 false.
	void			setAttribute(Component* ref, Direction dir, float speed,bool isPhysical = true);

	CREATE_FUNC(MoveState);

private:
	cocos2d::Point getMovedPos(cocos2d::Point nowPos, Direction dir, float speed);

	Direction		m_Direction;
	float			m_Speed;
	bool			m_IsPhysics;
};

END_NS_AT