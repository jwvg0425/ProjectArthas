/************************************************************************/
/*
CLASS			: SeizeFireTrigger
Author			: 김연우
역할				: 공격 중지 트리거
최종 수정일자	: 2014-11-12
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Trigger.h"

BEGIN_NS_AT

class SeizeFireTrigger : public Trigger
{
public:
	void					initTrigger(int signifier);
	virtual bool			operator ==( const Trigger& trigger );

	SeizeFireTrigger();

private:
};

END_NS_AT