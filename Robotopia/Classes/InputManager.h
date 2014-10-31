/************************************************************************/
/*
CLASS			: InputManager
Author			: 남현욱
역할				: 전체 키 배열의 상태를 저장 관리한다. 
최종 수정일자	: 2014-10-29
최종 수정자		:
최종 수정사유	:
Comment			:
*/
/************************************************************************/

#pragma once
#include "Util.h"
#include "cocos2d.h"
#define MAX_KEY_NUM	255

BEGIN_NS_AT

class InputManager : public cocos2d::Node
{
public:
	InputManager();
	~InputManager();

	bool						init();
	void						initKeyState();
	KeyState					getKeyState(KeyCode keyCode);
	void						getKeyStates(OUT KeyState* keyStates);
	void						receiveKeyboardData(cocos2d::EventDispatcher* eventDispatcher, cocos2d::Node* receiver);

	void						onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void						onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

private:
	KeyState		m_KeyStates[MAX_KEY_NUM];
};

END_NS_AT