#pragma once

#include "Component.h"
#include "cocos2d.h"

enum keyState
{
	KEY_LEFT = 1,
	KEY_RIGHT = 2,
	KEY_JUMP = 4,
};

class CommandComponent : public Component
{
public:
	CommandComponent(Object* parent);
	~CommandComponent();

	virtual void update(float dTime);
	virtual void enter();
	virtual void exit();

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
protected:
	int m_KeyStates;
};