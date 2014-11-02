/************************************************************************/
/*
CLASS			: PlayerRender
Author			: 김성연
역할				: Player가 그릴 수 있는 Transition 목록 가지고 있고 그려줌
최종 수정일자		: 2014-10-31
최종 수정자		:
최종 수정사유		:
Comment			: PlayerRender에 어떤 목록이 들어갈지 정해야 됩니다. 
*/
/************************************************************************/

#pragma once
#include "RenderComponent.h"
#include "cocos2d.h"

BEGIN_NS_AT

class PlayerRender : public RenderComponent
{
public:
	OVERRIDE bool init();
	OVERRIDE void enter();
	OVERRIDE void exit();
	
	OVERRIDE bool initRender();
	
	CREATE_FUNC(PlayerRender);
private:

};

END_NS_AT
