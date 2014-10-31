/************************************************************************/
/*
CLASS			: DataType
Author			: 남현욱
역할				: enum 및 typedef 등 프로젝트 내에서 쓰이는 
				  각종 고유 정의 타입들 보유 
최종 수정일자		: 2014-10-29
최종 수정자		: 남현욱
최종 수정사유		: PlayerInfo DataType 추가 및 순서 변경
Comment			: 이런 형식으로 앞으로 바꾸는 사람이 있으면 정리 하세요
*/
/************************************************************************/

#pragma once
#include <vector>
class Trigger;
class StateComponent;

BEGIN_NS_AT

enum DirectionBit
{
	DIR_NONE = 0,
	DIR_UP = 1,
	DIR_RIGHT =2,
	DIR_DOWN = 4,
	DIR_LEFT = 8,
	DIR_MAX = 16,
};

typedef char Direction;

enum ComponentType
{
	
	//Object Type
	OT_NONE = 0,

	OT_CHARACTER_START = 1,
	OT_PLAYER = OT_CHARACTER_START,
	OT_CHARACTER_END,
	
	OT_TILE_START = 101,
	OT_BLOCK = OT_TILE_START,
	OT_TILE_END,

	//Trigger Type
	TT_START = 1001,
	TT_STATE_CHANGE = TT_START,
	TT_CONTACT = TT_START + 1,
	TT_END,

	//Component Type
	CT_COMPONENT_START = 2001,
	CT_COMMAND_COMPONENT,
	CT_FSM_COMPONENT,
	CT_OBSERVER_COMPONENT,
	CT_PHYSICS_COMPONENT,
	CT_RENDER_COMPONENT,
	CT_SPRITE_COMPONENT,
	CT_STATE_COMPONENT,
	CT_COMPONENT_END,
};

enum EffectType
{
	ET_PLAYER_MISSILE_MELEE,

};

struct ModuleData
{
	size_t width;
	size_t height;
	std::vector<ComponentType> data;
};

typedef std::pair<Trigger*, StateComponent*> Transition;

struct PlayerInfo
{
	int maxHp;
	int maxSteam;
	int hp;
	int steam;
};

END_NS_AT