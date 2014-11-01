/************************************************************************/
/*
	CLASS			: ComponentType
	Author			: 남현욱
	역할				: Resource들의 Type 값 정의 enum 관리.
	최종 수정일자		: 2014-11-1
	최종 수정자		: 남현욱
	최종 수정사유		: 김성연	
	Comment			: PLAYER ANIMATION TYPE 추가
*/
/************************************************************************/

#pragma once
#include "Macro.h"

BEGIN_NS_AT


enum ResourceType
{
	//Sprite Type
	ST_START = 0,
	ST_PLAYER = ST_START,
	ST_BLOCK = ST_START + 1,
	ST_END,

	//Animation Type
	AT_START = 500,
	AT_PLAYER = AT_START,
	AT_PLAYER_IDLE,
	AT_PLAYER_MOVE,
	AT_PLAYER_JUMP,
	AT_END,
};


END_NS_AT