/************************************************************************/
/*
	CLASS			: Floor
	Author			: 김연우
	역할				: 아래 충돌만 하는 타일 Floor
	최종 수정일자	: 2014-11-09
	최종 수정자		:
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/
#pragma once
#include "Tile.h"
#include "Util.h"



class Floor : public Tile
{
public:
	OVERRIDE bool	init();
	OVERRIDE void	update(float dTime);
	OVERRIDE void	enter();
	OVERRIDE void	exit();
	OVERRIDE void	initTile(cocos2d::Rect tileRect);
	void			extendBlock(cocos2d::Rect tileRect);

	CREATE_FUNC(Floor);
private:
	OVERRIDE void	initPhysicsBody(cocos2d::Rect physicsRect, PhysicsCategory categoryBitmask /*= PHYC_ALL*/);

};

