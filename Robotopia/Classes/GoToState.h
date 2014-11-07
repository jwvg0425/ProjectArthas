/************************************************************************/
/*
	CLASS			: GoToState
	Author			: 김연우
	역할				: 특정 지점까지만 움직이는 상태
	최종 수정일자	: 2014-11-07
	최종 수정자		:
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/

#pragma once
#include "StateComponent.h"
#include "cocos2d.h"

BEGIN_NS_AT

class GoToState : public StateComponent
{
public:
	OVERRIDE bool	init();
	OVERRIDE void	enter();
	OVERRIDE void	exit();
	OVERRIDE void	update(float dTime);

	void			initState(Component* subject, cocos2d::Point dstPos, float requiredTime);

	CREATE_FUNC(GoToState);

private:
	cocos2d::Point	getMovingVelocity(cocos2d::Point srcPos, cocos2d::Point dstPos, float requiredTime);
	bool			isAlmostThere(cocos2d::Point currentPos);

	float			m_RequiredTime;
	cocos2d::Point	m_Destination;
	cocos2d::Vect	m_Velocity;
};

END_NS_AT