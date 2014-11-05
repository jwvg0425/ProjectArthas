/************************************************************************/
/*
CLASS			: InputManager
Author			: 남현욱
역할				: 전체 키 배열의 상태를 저장 관리한다. 
최종 수정일자	: 2014-10-29
최종 수정자		: 우재우
최종 수정사유	: 마우스 입력 추가했습니다.
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "cocos2d.h"

BEGIN_NS_AT

class InputManager
{
	friend class InputSentinel;
public:
	InputManager();
	~InputManager();

	//Keyboard
	bool					init();
	void					initKeyState();
	KeyState				getKeyState(KeyCode keyCode);
	void					getKeyStates(OUT KeyState* keyStates);
	void					receiveKeyboardData(cocos2d::Layer* layer);

	//Mouse
	void					initMouseState();
	void					receiveMouseData(cocos2d::Layer* layer);
	void					resetMouseInfo();
	MouseInfo				getMouseInfo();

private:
	//Keyboard
	void					adjustKeyState(KeyCode keyCode);

	KeyState				m_KeyStates[MAX_KEY_NUM];
	int						m_KeyTime[MAX_KEY_NUM];

	//Mouse
	void					checkDoubleClick();

	int						m_WinWidth;
	int						m_WinHeight;
	int						m_MouseTime;
	MouseInfo				m_MouseInfo;

};

class InputSentinel : public cocos2d::Node
{
	friend class InputManager;

	OVERRIDE bool init();

	CREATE_FUNC(InputSentinel);

public:
	void					onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void					onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void					onMouseDown(cocos2d::Event* event);
	void					onMouseUp(cocos2d::Event* event);
	void					onMouseMove(cocos2d::Event* event);
};

END_NS_AT