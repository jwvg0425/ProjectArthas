/************************************************************************/
/*
	CLASS			: ComponentType
	Author			: 남현욱
	역할				: Input과 관련된 enum 값 정의.
	최종 수정일자	: 2014-11-1
	최종 수정자		: 남현욱
	최종 수정사유	: 
	Comment			: 
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "cocos2d.h"

#define MOUSEBUTTON 2

BEGIN_NS_AT

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
	MS_LEFT_CLICK,
	MS_RIGHT_CLICK,
};

struct MouseInfo
{
	cocos2d::Point	mouseStart[MOUSEBUTTON];
	cocos2d::Point	mouseMove;
	cocos2d::Point	mouseEnd[MOUSEBUTTON];
	bool			dragOn;
	MouseState		mouseState;
};

END_NS_AT