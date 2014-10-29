/************************************************************************/
/*
CLASS			: Trigger
Author			: 김연우
역할				: 상태변경 트리거 추상클래스
최종 수정일자	: 2014-10-29
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Util.h"

BEGIN_NS_AT

class Trigger
{
public:
	int getType()
	{
		return m_Type;
	}
	virtual bool operator ==( Trigger& trigger ) = 0;
protected:
	int m_Type;
};

END_NS_AT