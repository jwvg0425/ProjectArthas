/************************************************************************/
/*
CLASS			: DashEffect
Author			: 남현욱
역할				: DashEffect class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: Dash할 때 나오는 이펙트
*/
/************************************************************************/
#pragma once
#include "Effect.h"

class DashEffect : public Effect
{
public:
	virtual bool				init();
	virtual void				enter();
	virtual void				exit();
	virtual void				update(float dTime);
	virtual void				dead();

	CREATE_FUNC(DashEffect);
	void endAnimation(cocos2d::Ref* sender);
private:
};