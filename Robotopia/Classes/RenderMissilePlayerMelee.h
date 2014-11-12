/************************************************************************/
/*
CLASS			: RenderMissilePlayerMelee
Author			: 김성연
역할				: Player Melee Missile 그려줌
최종 수정일자		: 2014-11-12
최종 수정자		:
최종 수정사유		:
Comment			: PlayerRender에 어떤 목록이 들어갈지 정해야 됩니다.
*/
/************************************************************************/

#pragma once
#include "RenderComponent.h"

BEGIN_NS_AT

class RenderMissilePlayerMelee : public RenderComponent
{
public:
	OVERRIDE bool init();
	OVERRIDE void enter();
	OVERRIDE void exit();

	OVERRIDE void initRender();

	CREATE_FUNC(RenderMissilePlayerMelee);
private:

};

END_NS_AT

