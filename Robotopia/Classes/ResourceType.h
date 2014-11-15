﻿/************************************************************************/
/*
	CLASS			: ComponentType
	Author			: 남현욱
	역할				: Resource들의 Type 값 정의 enum 관리.
	최종 수정일자		: 2014-11-07
	최종 수정자		: 남현욱
	최종 수정사유		: 김성연	
	Comment			: ST_BLOCK_TURRET 추가
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
	ST_BLOCK,
	ST_BLOCK_MOVING,
	ST_FLOOR,
	ST_BLOCK_TURRET,
	ST_PORTAL,
	ST_TRAP_UNDERGROUND,
	ST_ETC_END,
	ST_STEAM_START=5000,
	ST_STEAM_MONKEY_00,
	ST_STEAM_MONKEY_01,
	ST_STEAM_MONKEY_02,
	ST_STEAM_MONKEY_03,
	ST_STEAM_MONKEY_04,
	ST_STEAM_MONKEY_05,
	ST_STEAM_EAGLE_00,
	ST_STEAM_EAGLE_01,
	ST_STEAM_EAGLE_02,
	ST_STEAM_EAGLE_03,
	ST_STEAM_EAGLE_04,
	ST_STEAM_EAGLE_05,
	ST_STEAM_BEAR_00,
	ST_STEAM_BEAR_01,
	ST_STEAM_BEAR_02,
	ST_STEAM_BEAR_03,
	ST_STEAM_BEAR_04,
	ST_STEAM_BEAR_05,
	ST_STEAM_MASK_HALF,
	ST_STEAM_MASK_PART,
	ST_STEAM_END,
	ST_GEAR_START=5050,
	ST_GEAR_FIXED_00,
	ST_GEAR_FIXED_01,
	ST_GEAR_ROTATE_00,
	ST_GEAR_ROTATE_01,
	ST_GEAR_ROTATE_02,
	ST_GEAR_ICON_BEAR,
	ST_GEAR_ICON_EAGLE,
	ST_GEAR_ICON_MONKEY,
	ST_GEAR_END,
	ST_MAPWIN_START = 5100,
	ST_MAPWIN_FRAME,
	ST_MAPWIN_TRIGGER,
	ST_MAPWIN_END,
	ST_MINIMAP_START = 5150,
	ST_MINIMAP_ROTATE_00,
	ST_MINIMAP_ROTATE_01,
	ST_MINIMAP_ROTATE_02,
	ST_MINIMAP_MASK,
	ST_MINIMAP_END,
	ST_CHARWIN_START = 5200,
	ST_CHARWIN_FRAME,
	ST_CHARWIN_TRIGGER,
	ST_CHARWIN_END,
	ST_MAPTOOL_START = 10000,
	ST_MAPTOOL_BLOCK,
	ST_MAPTOOL_FLOOR,
	ST_MAPTOOL_PORTAL,
	ST_MAPTOOL_BLOCK_RANDOM,
	ST_MAPTOOL_FLOOR_RANDOM,
	ST_MAPTOOL_TRAP_RANDOM,
	ST_MAPTOOL_MONSTER_RANDOM,
	ST_MAPTOOL_END,
	ST_END,

	//Animation Type
	AT_START = 500,
	AT_PLAYER = AT_START,
	AT_PLAYER_IDLE,
	AT_PLAYER_MOVE,
	AT_PLAYER_JUMP,
	AT_PLAYER_END,

	AT_MISSILE_START = 600,
	AT_MISSILE_PLAYER_MELEE,
	AT_MISSILE_PLAYER_LINEAR,
	AT_MISSILE_END,

	AT_TRAP_START = 700,
	AT_TRAP_UNDERGROUND,
	AT_TRAP_END,

	AT_MONSTER_START = 800,
	AT_MONSTER_STAND_SHOT_IDLE,
	AT_MONSTER_STAND_SHOT_ATTACK,
	AT_MONSTER_END,

	AT_END,
};


END_NS_AT