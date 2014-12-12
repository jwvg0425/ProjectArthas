/************************************************************************/
/*
CLASS			: MissileThunder
Author			: 김성연
역할				: Devil이 사용 할 번개 미사일
최종 수정일자		: 2014-12-12
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once

#include "Missile.h"
#include "Util.h"

class MissileThunder : public Missile
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


	CREATE_FUNC(MissileThunder);

private:
	cocos2d::Sprite*			m_ThunderSprite = nullptr;
	cocos2d::Sprite*			m_ArrowSprite = nullptr;
	cocos2d::Point				m_TargetPos;
	int						    m_ArrowStartTime = 0;
	int							m_ThunderStartTime = 0;
	bool						m_IsAttacking = false;
	bool						m_ArrowSpriteEnd = false;


};

