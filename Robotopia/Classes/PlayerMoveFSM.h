﻿/************************************************************************/
/*
CLASS			: PlayerMoveFSM
Author			: 남현욱
역할				: PlayerMoveFSM을 구현한 클래스.
최종 수정일자	: 2014-10-31
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Util.h"
#include "FSMComponent.h"



class PlayerMoveFSM : public FSMComponent
{
public:
	OVERRIDE bool				init();
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	CREATE_FUNC(PlayerMoveFSM);
private:
};

