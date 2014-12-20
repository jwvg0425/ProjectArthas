/************************************************************************/
/*
CLASS			: FlyRoundEffect
Author			: 남현욱
역할				: FlyRoundEffect class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: 날 때 나오는 이펙트.
*/
/************************************************************************/
#pragma once
#include "Effect.h"
#define OPACITY_CONSUME_VALUE 255


class FlyRoundEffect : public Effect
{
public:
	virtual bool				init();
	virtual void				enter();
	virtual void				exit();
	virtual void				update(float dTime);
	virtual void				dead();

	CREATE_FUNC(FlyRoundEffect);
private:
	float m_Opacity = 255;
	int   m_Sound = 0;
};