/************************************************************************/
/*
CLASS			: AICommand
Author			: 김성연
역할				: 몬스터들에 상황에 따라 트리거를 쏴줄 AI커맨드들의 추상클래스
최종 수정일자		: 2014-11-16
최종 수정자		:
최종 수정사유		:
Comment			:
*/
/************************************************************************/
#pragma once
#include "CommandComponent.h"



class AICommand : public CommandComponent
{
public:

	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	CREATE_FUNC(AICommand);

protected:

};

