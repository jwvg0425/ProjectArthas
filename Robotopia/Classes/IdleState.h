/************************************************************************/
/*
CLASS			: IdleState
Author			: 김성연
역할				: 기본 State를 나타냄 (아마 서있는상태)
최종 수정일자		: 2014-10-31
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/

#include "StateComponent.h"
#include "cocos2d.h"

BEGIN_NS_AT

class IdleState : public StateComponent
{
	OVERRIDE bool init();
	OVERRIDE void enter();
	OVERRIDE void exit();
	OVERRIDE void update(int dTime);
};

END_NS_AT