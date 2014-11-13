/************************************************************************/
/*
CLASS			: TrapUnderground
Author			: 김성연
역할				: 땅에서 주기적으로 공격하는 타일
최종 수정일자		: 2014-11-13
최종 수정자		:
최종 수정사유		:
Comment			: 사용하기 전에 initTile을 꼭 부르시오
*/
/************************************************************************/

#pragma once
#include "Tile.h"

BEGIN_NS_AT

class TrapUnderground : public Tile
{
public:
	OVERRIDE bool init();
	OVERRIDE void update(float dTime);
	OVERRIDE void enter();
	OVERRIDE void exit();

	OVERRIDE void initTile(cocos2d::Point origin, cocos2d::Size physicalSize, cocos2d::Size spriteSize);

private:
	long	m_StartTime;
	long	m_AccumulatedTime;
	long	m_Duration;
	bool	m_IsPrevTimeCheck;



};

END_NS_AT