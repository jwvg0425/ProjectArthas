﻿/************************************************************************/
/*
CLASS			: Missile
Author			: 김성연
역할				: 각종 미사일의 최상위 부모 클래스
최종 수정일자		: 2014-11-12
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once

#include "BaseComponent.h"
#include "Util.h"



class Missile : public BaseComponent
{
public:
	enum MissileState
	{
		MST_NONE = 0,
		MST_KNOCKBACK = 1,
		MST_BIND = 2,
		MST_NUM
	};

	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	virtual void				dead();

	ABSTRACT void			    initMissile() = 0;
	ABSTRACT void				setAttribute(cocos2d::Point pos, Direction attackDir, 
											 float damage,  
											 cocos2d::Size contentsSize, cocos2d::Vec2 velocity,
											 cocos2d::Point targetPos) = 0;
	
	MissileState				getState();
	void						setState(MissileState state);
	bool						isUsable() const ;
	float						getDamage() const;
	bool						isPlayerMissile() const;
	int							getAttackDir();


protected:
	bool						m_IsPlayerMissile = false;
	bool						m_IsUsable = true;
	float						m_Damage = 0.0f;
	cocos2d::Vec2				m_Velocity = { 0, 0 };
	Direction					m_AttackDir = DIR_NONE;
	cocos2d::Point				m_TargetPos = { 0, 0 };
	cocos2d::PhysicsBody*		m_Body = nullptr;
	MissileState				m_State = MST_NONE;
};

