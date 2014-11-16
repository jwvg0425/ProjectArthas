/************************************************************************/
/*
CLASS			: MovingBlock
Author			: 김연우
역할			: 움직이는 타일 MovingBlock
최종 수정일자	: 2014-11-05
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/

#pragma once
#include "Block.h"
#include "Util.h"



class MovingBlock : public Tile
{
public:
	OVERRIDE bool	init();
	OVERRIDE void	update(float dTime);
	OVERRIDE void	enter();
	OVERRIDE void	exit();

	OVERRIDE void	initTile(cocos2d::Rect tileRect);
	
	CREATE_FUNC(MovingBlock);

private:
	void			initFSM(cocos2d::Point leftPoint, cocos2d::Point rightPoint, float time);
	void			move(float dTime);
};

