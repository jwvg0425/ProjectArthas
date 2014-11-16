/************************************************************************/
/*
	CLASS			: Block
	Author			: 김연우
	역할				: 타일의 대명사 Block Class
	최종 수정일자	: 2014-10-29
	최종 수정자		:
	최종 수정사유	:
	Comment			:
*/
/************************************************************************/
#pragma once
#include "Tile.h"
#include "Util.h"



class Block : public Tile
{
public:
	OVERRIDE bool	init();
	OVERRIDE void	update( float dTime );
	OVERRIDE void	enter();
	OVERRIDE void	exit();

	OVERRIDE void	initTile(cocos2d::Rect tileRect);
	void			extendBlock(cocos2d::Rect rect);
	CREATE_FUNC(Block);
	
private:
	OVERRIDE void	initPhysicsBody(cocos2d::Rect physicsRect, PhysicsCategory categoryBitmask = PHYC_ALL);
};

