/************************************************************************/
/*
CLASS			: ExplosionEffect
Author			: 남현욱
역할				: ExplosionEffect class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: 폭발 이펙트
*/
/************************************************************************/
#pragma once
#include "Effect.h"

class ExplosionEffect : public Effect
{
public:
	virtual bool				init();
	virtual void				enter();
	virtual void				exit();
	virtual void				update(float dTime);
	virtual void				dead();

	CREATE_FUNC(ExplosionEffect);
	void						endAnimation(cocos2d::Ref* sender);
private:
};