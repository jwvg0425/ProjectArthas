/************************************************************************/
/*
CLASS			: PositionTrigger
Author			: 김연우
역할				: 특정 위치에 도달했을때 발생하는 트리거 클라스
최종 수정일자	: 2014-11-05
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Trigger.h"

BEGIN_NS_AT

class PositionTrigger : public Trigger
{
public:
	void					initPositionTrigger(cocos2d::Point point);
	virtual bool			operator ==( Trigger& trigger );
	const cocos2d::Point	getTriggerPoint();
	PositionTrigger();
	~PositionTrigger();

private:
	cocos2d::Point m_TriggerPoint;
};

END_NS_AT