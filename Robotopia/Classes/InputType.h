/************************************************************************/
/*
	CLASS			: ComponentType
	Author			: 남현욱
	역할				: Input과 관련된 enum 값 정의.
	최종 수정일자	: 2014-11-14
	최종 수정자		: 김연우
	최종 수정사유	: CommandType추가
	Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "cocos2d.h"

#define LEFT_CLICK_POINT 0
#define RIGHT_CLICK_POINT 1
#define MOUSEBUTTON 2

enum KeyCode
{
	KC_NONE = 0,
	KC_UP = cocos2d::EventKeyboard::KeyCode::KEY_W,
	KC_RIGHT = cocos2d::EventKeyboard::KeyCode::KEY_D,
	KC_DOWN = cocos2d::EventKeyboard::KeyCode::KEY_S,
	KC_LEFT = cocos2d::EventKeyboard::KeyCode::KEY_A,
	KC_FLY = cocos2d::EventKeyboard::KeyCode::KEY_SHIFT,
	KC_ATTACK = cocos2d::EventKeyboard::KeyCode::KEY_F3,
	KC_CHARACTER = cocos2d::EventKeyboard::KeyCode::KEY_C,
	KC_MAP = cocos2d::EventKeyboard::KeyCode::KEY_M,
	KC_TAB = cocos2d::EventKeyboard::KeyCode::KEY_TAB,
	KC_JUMP = cocos2d::EventKeyboard::KeyCode::KEY_SPACE,
	KC_RETURN = cocos2d::EventKeyboard::KeyCode::KEY_ENTER,
	KC_ESC = cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE,
	KC_GEAR_EAGLE = cocos2d::EventKeyboard::KeyCode::KEY_3,
	KC_GEAR_BEAR = cocos2d::EventKeyboard::KeyCode::KEY_1,
	KC_GEAR_MONKEY = cocos2d::EventKeyboard::KeyCode::KEY_2,
	KC_TEST = cocos2d::EventKeyboard::KeyCode::KEY_F1,
	KC_TEST2 = cocos2d::EventKeyboard::KeyCode::KEY_F2,
	KC_DOWN_JUMP,
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
	MS_NONE = 0,
	MS_LEFT_DOWN,
	MS_RIGHT_DOWN,
	MS_LEFT_UP,
	MS_RIGHT_UP,
};

struct MouseInfo
{
	cocos2d::Point	mouseStart[MOUSEBUTTON];
	cocos2d::Point	mouseMove;
	cocos2d::Point	mouseEnd[MOUSEBUTTON];
	bool			dragOn;
	bool			doubleClick;
	MouseState		mouseState;
};

