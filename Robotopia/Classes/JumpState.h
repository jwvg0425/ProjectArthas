/************************************************************************/
/*
CLASS			: JumpState
Author			: 남현욱
역할				: 점프중인 상태에 해당하는 클래스.
최종 수정일자		: 2014-10-31
최종 수정자		:
최종 수정사유		:
Comment			: 반드시 PhysicsComponent가 있어야만 정상 동작함.
*/
/************************************************************************/

#pragma once
#include "StateComponent.h"
#include "cocos2d.h"



class JumpState : public StateComponent
{
public:
	OVERRIDE bool	init();
	OVERRIDE void	enter();
	OVERRIDE void	exit();
	OVERRIDE void	update(float dTime);

	void			setAttribute(BaseComponent* ref, float speed, bool isDownJump);

	CREATE_FUNC(JumpState);

private:
	float			m_Speed;
	bool			m_IsDownJump;
};

