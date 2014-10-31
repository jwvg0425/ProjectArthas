/************************************************************************/
/*
CLASS			: PlayerFSMComponent
Author			: 남현욱
역할				: PlayerFSM을 구현한 클래스.
최종 수정일자	: 2014-10-31
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Util.h"
#include "FSMComponent.h"

BEGIN_NS_AT

class PlayerFSM : public FSMComponent
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	CREATE_FUNC(PlayerFSM);
private:
};

END_NS_AT