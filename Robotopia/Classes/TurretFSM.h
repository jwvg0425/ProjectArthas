/************************************************************************/
/*
CLASS			: TurretFSM
Author			: 김성연
역할				: 한 자리에서 공격하는 Turret의 FSM
최종 수정일자		: 2014-11-07
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/

#pragma once
#include "FSMComponent.h"
#include "cocos2d.h"

BEGIN_NS_AT

class TurretFSM : public FSMComponent
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	void						initTurretFSM();


	CREATE_FUNC(TurretFSM);
private:
};


END_NS_AT