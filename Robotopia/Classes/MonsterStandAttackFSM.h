/************************************************************************/
/*
CLASS			: MonsterStandAttackFSM
Author			: 김성연
역할				: MonsterStandAttack입니다
최종 수정일자		: 2014-11-16
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "FSMComponent.h"

BEGIN_NS_AT

class MonsterStandAttackFSM : public FSMComponent
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				enter();
	OVERRIDE void				exit();
	OVERRIDE void				update(float dTime);
	void						initFSM();

	CREATE_FUNC(MonsterStandAttackFSM);
private:


};

END_NS_AT