/************************************************************************/
/*
CLASS			: ParalysisEffect
Author			: 남현욱
역할				: ParalysisEffect class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: 마비 상태 걸릴 때 나오는 이펙트
*/
/************************************************************************/
#pragma once
#include "Effect.h"

class ParalysisEffect : public Effect
{
public:
	virtual bool				init();
	virtual void				enter();
	virtual void				exit();
	virtual void				update(float dTime);
	virtual void				dead();

	CREATE_FUNC(ParalysisEffect);
	void endAnimation(cocos2d::Ref* sender);
private:
};