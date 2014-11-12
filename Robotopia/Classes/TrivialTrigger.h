/************************************************************************/
/*
CLASS			: TrivialTrigger
Author			: 김연우
역할				: 그냥 정수 입력해서 간단한 트리거 만들 수 있게 함.
최종 수정일자	: 2014-11-12
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Trigger.h"

BEGIN_NS_AT

class TrivialTrigger : public Trigger
{
public:
	void					initTrigger(int signifier);
	virtual bool			operator ==( const Trigger& trigger );
	int						getSignifier();

	TrivialTrigger();

private:
	int	m_Signifier;
};

END_NS_AT