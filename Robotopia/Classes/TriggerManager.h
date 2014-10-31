/************************************************************************/
/*
CLASS			: TriggerManager
Author			: 남현욱
역할				: 각종 트리거를 생성해주는 매니저.
최종 수정일자	: 2014-10-29
최종 수정자		:
최종 수정사유	:
Comment			: 트리거 생성 후 각 트리거 값을 초기화해주는 것을 잊지 말 것.
*/
/************************************************************************/

#pragma once
#include "Util.h"

BEGIN_NS_AT

class Trigger;

class TriggerManager
{
public:
	TriggerManager();
	~TriggerManager();

	bool init();

	Trigger* createTrigger(TriggerType type);
private:
};

END_NS_AT