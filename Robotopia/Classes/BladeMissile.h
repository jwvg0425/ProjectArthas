/************************************************************************/
/*
CLASS			: BladeMissile
Author			: 남현욱
역할			: Player의 근접 공격 중 Blade를 할 때의 미사일.
최종 수정일자	: 2014-11-12
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once


#include "Missile.h"
#include "Util.h"


class SpriteComponent;
class BladeMissile : public Missile
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

	virtual bool				onContactBegin(cocos2d::PhysicsContact& contact);
	virtual void				setEnabled(bool enable);

	CREATE_FUNC(BladeMissile);

private:
	void						endAnimation(cocos2d::Ref* sender);

	cocos2d::Sprite*			m_Sprite = nullptr;
	int							m_StartTime = 0;
	cocos2d::Size				m_TargetSize;
};