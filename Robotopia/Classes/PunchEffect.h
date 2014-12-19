/************************************************************************/
/*
CLASS			: PunchEffect
Author			: 남현욱
역할				: PunchEffect class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: punch할 때 나오는 이펙트
*/
/************************************************************************/
#pragma once
#include "Effect.h"

class PunchEffect : public Effect
{
public:
	virtual bool				init();
	virtual void				enter();
	virtual void				exit();
	virtual void				update(float dTime);
	virtual void				dead();

	CREATE_FUNC(PunchEffect);
	void endAnimation(cocos2d::Ref* sender);
private:
};