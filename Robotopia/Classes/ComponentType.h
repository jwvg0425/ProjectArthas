/************************************************************************/
/*
	CLASS			: ComponentType
	Author			: 남현욱
	역할				: Component들의 Type 값 정의 enum 관리.
	최종 수정일자	: 2014-11-1
	최종 수정자		: 남현욱
	최종 수정사유	: 
	Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"

BEGIN_NS_AT

enum ComponentType
{
	//Component Type
	CT_NONE = 0,
	CT_COMPONENT_START = 0,
	CT_OBSERVER,
	CT_PHYSICS,
	CT_ANIMATION,
	CT_SPRITE,
	CT_RENDER,
	CT_COMMAND,
	CT_FSM,
	CT_STATE,

		////Render Type
		RNDT_START = 101,
		RNDT_END,

		////Command Type
		CMDT_START = 201,
		CMDT_END,

		////FSM Type
		FSMT_START = 301,
		FSMT_PLAYER_MOVE,
		FSMT_PLAYER_JUMP,
		FSMT_END,

		////State Type
		STAT_START = 401,
		STAT_IDLE,
		STAT_MOVE,
		STAT_MOVE_LEFT,
		STAT_MOVE_RIGHT,
		STAT_JUMP,
		STAT_END,

		//Object Type
		OT_NONE = 0,

		OT_CHARACTER_START = 1001,
		OT_PLAYER,
		OT_CHARACTER_END,

		OT_TILE_START = 1101,
		OT_BLOCK,
		OT_TILE_END,

	CT_COMPONENT_END,

};

END_NS_AT