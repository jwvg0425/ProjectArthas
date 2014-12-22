/************************************************************************/
/*
CLASS			: SmokeEffect
Author			: 남현욱
역할				: SmokeEffect class
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: 스팀 다 떨어져갈 때 나오는 이펙트.
*/
/************************************************************************/
#pragma once
#include "FlyRoundEffect.h"
#define OPACITY_CONSUME_VALUE 255


class SmokeEffect : public FlyRoundEffect
{
public:
	virtual bool				init();
	virtual void				enter();
	virtual void				exit();
	virtual void				update(float dTime);
	virtual void				dead();

	CREATE_FUNC(SmokeEffect);
private:
	float m_Opacity = 255;
};