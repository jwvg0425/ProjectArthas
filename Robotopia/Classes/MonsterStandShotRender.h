/************************************************************************/
/*
CLASS			: MonsgerStandShotRender
Author			: 김성연
역할				: 
최종 수정일자		: 2014-11-15
최종 수정자		:
최종 수정사유		:
Comment			: 
*/
/************************************************************************/

#pragma once
#include "RenderComponent.h"
#include "cocos2d.h"

BEGIN_NS_AT

class MonsterStandShotRender : public RenderComponent
{
public:
	OVERRIDE bool init();
	OVERRIDE void enter();
	OVERRIDE void exit();

	OVERRIDE void initRender();

	CREATE_FUNC(MonsterStandShotRender);
private:

};

END_NS_AT