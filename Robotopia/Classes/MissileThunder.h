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

class AnimationComponent;
class MissileThunder : public Missile
{
public:
	virtual bool				init();
	virtual void				update(float dTime);
	virtual void				enter();
	virtual void				exit();
	virtual	void				dead();

	virtual void			    initMissile();
	virtual void				setAttribute(cocos2d::Point pos, Direction attackDir = DIR_NONE,
											 float damage = 0,
											 cocos2d::Size contentsSize = cocos2d::Size::ZERO,
											 cocos2d::Vec2 velocity = cocos2d::Point::ZERO,
											 cocos2d::Point targetPos = cocos2d::Point::ZERO);
	virtual void				setEnabled(bool enable);


	CREATE_FUNC(MissileThunder);

private:
	cocos2d::Sprite*			m_ThunderSprite = nullptr;
	cocos2d::Point				m_TargetPos;
	AnimationComponent*			m_ThunderAniComponent = nullptr;
	bool						m_ThunderTurn = false;
	int							m_StartTime = 0;
	int							m_Duration = 0;

};

