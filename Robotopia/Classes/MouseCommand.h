/************************************************************************/
/*
CLASS			: MouseComponent
Author			: 우재우
역할			: 마우스 커맨드
최종 수정일자	: 2014-11-04
최종 수정자		: 우재우
최종 수정사유	: 신규
Comment			:
*/
/************************************************************************/
#pragma once
#include "CommandComponent.h"
#include "cocos2d.h"


class MouseCommand : public CommandComponent
{
public:

	OVERRIDE bool				init();
	OVERRIDE void				update(float dTime);
	OVERRIDE void				enter();
	OVERRIDE void				exit();

	CREATE_FUNC(MouseCommand);

protected:

};

