/************************************************************************/
/*
CLASS			: MissilePlayerLinear
Author			: 김성연
역할				: Player의 Linear Missile에 관한 내용 가지고 있음
최종 수정일자		: 2014-11-15
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once

#include "Missile.h"
#include "Util.h"



class MissilePlayerLinear : public Missile
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	OVERRIDE void			    initMissile();
	OVERRIDE void				setAttribute(cocos2d::Point pos, Direction attackDir = DIR_NONE,
											 float damage = 0,
											 cocos2d::Size contentsSize = cocos2d::Size::ZERO,
											 cocos2d::Vec2 velocity = cocos2d::Point::ZERO,
											 cocos2d::Point targetPos = cocos2d::Point::ZERO);


	CREATE_FUNC(MissilePlayerLinear);

private:
	int						m_MovedDistance = 0;
	cocos2d::Point			m_StartPos = { 0, 0 };
	cocos2d::Point			m_CurPos = { 0, 0 };
	bool					m_IsStartPosCheck = true;


};

