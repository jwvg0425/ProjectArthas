/************************************************************************/
/*
CLASS			: CoinEffect
Author			: 남현욱
역할				: CoinEffect class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: 동전 이펙트
*/
/************************************************************************/
#pragma once
#include "Effect.h"

class CoinEffect : public Effect
{
public:
	virtual bool				init();
	virtual void				enter();
	virtual void				exit();
	virtual void				update(float dTime);
	virtual void				dead();

	CREATE_FUNC(CoinEffect);
	void endAnimation(cocos2d::Ref* sender);
private:
};