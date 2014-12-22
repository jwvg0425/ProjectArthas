/************************************************************************/
/*
CLASS			: HPKit
Author			: 김성연
역할				: HP채워주는 kit
최종 수정일자		: 2014-12-20
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "ItemAbstract.h"

class AnimationComponent;
class HPKit : public ItemAbstract
{
public:
	virtual bool				init();
	virtual void				update(float dTime);
	virtual void				enter();
	virtual void				exit();
	virtual void				dead();
	virtual bool				onContactBegin(cocos2d::PhysicsContact& contact);
	virtual void				onContactSeparate(cocos2d::PhysicsContact& contact);


	CREATE_FUNC(HPKit);

private:
	AnimationComponent* m_HpAni = nullptr;
	cocos2d::Size		m_Size = cocos2d::Size::ZERO;
	cocos2d::Vec2		m_Velocity = cocos2d::Vec2::ZERO;
	bool				m_IsFirst = true;
	int					m_FirstCheckTime = 0;
	int					m_DownTime = 0;
	bool				m_IsExit = false;
	bool				m_IsGettable = false;
	int					m_WaitingCheckTime = 0;
};

