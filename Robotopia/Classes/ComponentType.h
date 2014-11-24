/************************************************************************/
/*
	CLASS			: ComponentType
	Author			: 남현욱
	역할				: BaseComponent들의 Type 값 정의 enum 관리.
	최종 수정일자	: 2014-11-1
	최종 수정자		: 남현욱
	최종 수정사유	: 
	Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"



enum ComponentType
{
	//BaseComponent Type
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
		FSMT_SIMPLE_ROAMING,
		FSMT_PLAYER_ATTACK,
		FSMT_END,

		////State Type
		STAT_START = 401,
		STAT_IDLE,
		STAT_MOVE,
		STAT_MOVE_LEFT,
		STAT_MOVE_RIGHT,
		STAT_JUMP,
		STAT_ATTACK,
		STAT_GOTO,
		STAT_END,

		////Render Type
		RENDER_START = 501,
		RENDER_PLAYER,
		RENDER_MISSILE_PLAYER_MELEE,

		//Info Type
		IT_START = 601,
		IT_COMMON,
		IT_BATTLE,
		IT_STEAM,
		IT_PHYSICS,
		IT_END,

		//Object Type
		OT_START = 1000,
		OT_PLAYER,

		OT_MONTER_START = 1011,
		OT_MONSTER,
		OT_MONSTER_STAND_SHOT,
		OT_MONSTER_END,

		OT_TILE_START = 1101,
		OT_BLOCK,
		OT_BLOCK_MOVING,
		OT_BLOCK_TURRET,
		OT_FLOOR,
		OT_PORTAL_OPEN,
		OT_PORTAL_CLOSED,
		OT_TRAP_UNDERGROUND,
		OT_TILE_END,

		OT_MISSILE_START = 1201,
		OT_MISSILE_PLAYER_MELEE,
		OT_MISSILE_PLAYER_LINEAR,
		OT_MISSILE_AIMING,
		OT_MISSILE_END,
		
		OT_END,

	CT_COMPONENT_END,

};

