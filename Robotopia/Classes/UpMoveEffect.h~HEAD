/************************************************************************/
/*
CLASS			: UpMoveEffect
Author			: 남현욱
역할				: UpMoveEffect class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: 위로 움직이는 이펙트
*/
/************************************************************************/
#pragma once
#include "Effect.h"

class UpMoveEffect : public Effect
{
public:
	virtual bool				init();
	virtual void				enter();
	virtual void				exit();
	virtual void				update(float dTime);
	virtual void				dead();
	void						setAnimation(AnimationType aniType);

	CREATE_FUNC(UpMoveEffect);
	void endAnimation(cocos2d::Ref* sender);
private:
};