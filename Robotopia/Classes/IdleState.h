/************************************************************************/
/*
CLASS			: IdleState
Author			: 김성연
역할				: 기본 State를 나타냄 (아마 서있는상태)
최종 수정일자		: 2014-10-31
최종 수정자		: 남현욱
최종 수정사유		: 2014-10-31
Comment			: State Type 반영이 안돼있어 이거 반영했습니다
*/
/************************************************************************/

#pragma once
#include "StateComponent.h"
#include "cocos2d.h"

BEGIN_NS_AT

class IdleState : public StateComponent
{
public:
	OVERRIDE bool init();
	OVERRIDE void enter();
	OVERRIDE void exit();
	OVERRIDE void update(float dTime);

	CREATE_FUNC(IdleState);

private:
};

END_NS_AT