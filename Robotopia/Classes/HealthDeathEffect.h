/************************************************************************/
/*
CLASS			: HealthDeathEffect
Author			: 남현욱
역할				: 
최종 수정일자	:
최종 수정자		:
최종 수정사유	:
Comment			: hp 다 떨어져서 죽을 때 나오는 이펙트.
*/
/************************************************************************/
#pragma once
#include "Effect.h"


class HealthDeathEffect : public Effect
{
public:
	virtual bool				init();
	virtual void				enter();
	virtual void				exit();
	virtual void				update(float dTime);
	virtual void				dead();

	CREATE_FUNC(HealthDeathEffect);
private:
	float		m_Opacity = 255;
	int			m_StartTime = 0;
	bool		m_MakeExplosion = false;
};