/************************************************************************/
/*
	CLASS			: PlayerAttackFSM
	Author			: 김연우
	역할				: PlayerAttackFSM을 구현한 클래스.
	최종 수정일자	: 2014-11-12
	최종 수정자		: 
	최종 수정사유	: 
	Comment			: 
*/
/************************************************************************/
#pragma once
#include "Util.h"
#include "FSMComponent.h"


class PlayerAttackFSM : public FSMComponent
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	CREATE_FUNC(PlayerAttackFSM);
private:
};

