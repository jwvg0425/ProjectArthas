/************************************************************************/
/*
CLASS			: AimingEffect
Author			: 남현욱
역할				: AimingEffect class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: AimingMissile 명중시 나오는 이펙트
*/
/************************************************************************/
#pragma once
#include "Effect.h"

class AimingEffect : public Effect
{
public:
	virtual bool				init();
	virtual void				enter();
	virtual void				exit();
	virtual void				update(float dTime);
	virtual void				dead();

	CREATE_FUNC(AimingEffect);
	void						endAnimation(cocos2d::Ref* sender);
private:
};