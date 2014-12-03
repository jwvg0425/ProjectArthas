/************************************************************************/
/*
CLASS			: TurretBlock
Author			: 김성연
역할				: 주기적으로 공격하는 블럭
최종 수정일자		: 2014-11-07
최종 수정자		:
최종 수정사유		:
Comment			: 만들고 반드시 setRect할 것!
*/
/************************************************************************/

#pragma once
#include <Tile.h>
#include "cocos2d.h"

class LaserCannon : public Tile
{
public:
	OVERRIDE bool init();
	OVERRIDE void update(float dTime);
	OVERRIDE void enter();
	OVERRIDE void exit();

	OVERRIDE void initTile(cocos2d::Rect tileRect);

	CREATE_FUNC(LaserCannon);
private:

	

};

