/************************************************************************/
/*
CLASS			: Portal
Author			: 김연우
역할				: 연결가능하면 열리고 아니면 닫히는 타일
최종 수정일자	: 2014-11-09
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/
#pragma once
#include "Tile.h"
#include "Util.h"

BEGIN_NS_AT

class Portal : public Tile
{
public:
	OVERRIDE bool init();
	OVERRIDE void update(float dTime);
	OVERRIDE void enter();
	OVERRIDE void exit();

	OVERRIDE void initTile(cocos2d::Point origin, cocos2d::Size physicalSize, cocos2d::Size spriteSize);


	CREATE_FUNC(Portal);

private:
	void		stateChange(ComponentType currentState);
	void		open();
	void		close();

	int			m_PositionIndex;
};

END_NS_AT