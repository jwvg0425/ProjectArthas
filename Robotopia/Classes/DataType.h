/************************************************************************/
/*
	CLASS			: DataType
	Author			: 남현욱
	역할				: enum 및 typedef 등 프로젝트 내에서 쓰이는
					  각종 고유 정의 타입들 보유
	최종 수정일자	: 2014-10-31
	최종 수정자		: 우재우
	최종 수정사유	: SceneType 추가
	Comment			: 이런 형식으로 앞으로 바꾸는 사람이 있으면 정리 하세요
*/
/************************************************************************/

#pragma once
#include <vector>
#include "cocos2d.h"

BEGIN_NS_AT

class Trigger;
class StateComponent;

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

enum SceneType
{
	TITLE_SCENE,
	LOADING_SCENE,
	GAME_SCENE,
};

enum ResourceType
{
	//Sprite Type
	ST_START = 0,
	ST_PLAYER = ST_START,
	ST_BLOCK = ST_START + 1,
	ST_END,

	//Animation Type
	AT_START = 500,
	AT_END,
};

enum ComponentType
{
	//Component Type
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
		FSMT_PLAYER = FSMT_START,
		FSMT_END,

		////State Type
		STAT_START = 401,
		STAT_IDLE = STAT_START,
		STAT_MOVE = STAT_START + 1,
		STAT_END,

		//Object Type
		OT_NONE = 0,

		OT_CHARACTER_START = 1001,
		OT_PLAYER = OT_CHARACTER_START,
		OT_CHARACTER_END,
	
		OT_TILE_START = 1101,
		OT_BLOCK = OT_TILE_START,
		OT_TILE_END,

	CT_COMPONENT_END,

};

enum TriggerType
{
	TT_NONE = 0,
	TT_STATE_CHANGE = 1,
	TT_CONTACT = 2,
	TT_KEYBOARD = 3,
	TT_NUM,
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

struct SpriteInfo
{
	ResourceType type;
	char spriteName[MAX_LEN];
};

struct AnimationInfo
{
	ResourceType type;
	char animationName[MAX_FRAME][MAX_LEN];
	int frameNum;
	float delay;
};

enum KeyCode
{
	KC_NONE = 0,
	KC_UP = cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW,
	KC_RIGHT = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
	KC_DOWN = cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW,
	KC_LEFT = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW,
	KC_FLY = cocos2d::EventKeyboard::KeyCode::KEY_SHIFT,
	KC_ATTACK = cocos2d::EventKeyboard::KeyCode::KEY_A,
	KC_JUMP = cocos2d::EventKeyboard::KeyCode::KEY_SPACE,
	KC_TEST = cocos2d::EventKeyboard::KeyCode::KEY_F1,
	KC_END,
};

enum KeyState
{
	KS_NONE = 0, // 뗀 상태
	KS_PRESS = 1, // 딱 누른 상태
	KS_HOLD = 2, // 눌려있는 상태
	KS_RELEASE = 4, //딱 뗀 상태
};

enum MouseState
{
	MS_NONE,
	MS_LEFT_DOWN,
	MS_LEFT_UP,
	MS_RIGHT_DOWN,
	MS_RIGHT_UP,
};

END_NS_AT