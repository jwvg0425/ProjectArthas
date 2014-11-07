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

BEGIN_NS_AT

class MovingBlock : public Tile
{
public:
	OVERRIDE bool	init();
	OVERRIDE void	update(float dTime);
	OVERRIDE void	enter();
	OVERRIDE void	exit();

	OVERRIDE void	initTile(float x, float y, float width, float height);
	OVERRIDE void	initTile(cocos2d::Rect rect);
	
	CREATE_FUNC(MovingBlock);

private:
	void			move(float dTime);

	float			m_LeftPoint;
	float			m_RightPoint;
	float			m_MovingSpeed;
	bool			m_isMovingRight;
};

END_NS_AT