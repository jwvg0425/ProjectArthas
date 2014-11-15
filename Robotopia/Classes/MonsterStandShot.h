/************************************************************************/
/*
CLASS			: MonsterStandShot
Author			: 김성연
역할				: 제자리서서 공격하는 몬스터
최종 수정일자		: 2014-11-15
최종 수정자		:
최종 수정사유		:
Comment			: 
*/
/************************************************************************/
#pragma once
#include "Util.h"
#include "Monster.h"

BEGIN_NS_AT

class MonsterStandShot : public Monster
{
public:
	OVERRIDE bool			init();
	OVERRIDE void			update(float dTime);
	OVERRIDE void			enter();
	OVERRIDE void			exit();
	OVERRIDE bool			initMosnter();

	CREATE_FUNC(MonsterStandShot);
private:

};

END_NS_AT