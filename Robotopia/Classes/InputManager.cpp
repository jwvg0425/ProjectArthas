#include "GameManager.h"
#include "InputManager.h"


Arthas::InputManager::InputManager()
{

}

Arthas::InputManager::~InputManager()
{

}

bool Arthas::InputManager::init()
{
	initKeyState();

	return true;
}

void Arthas::InputManager::initKeyState()
{
	for (int i = 0; i < MAX_KEY_NUM; i++)
	{
		m_KeyStates[i] = KS_NONE;
	}

	for (int i = 0; i < MAX_KEY_NUM; i++)
	{
		m_KeyTime[i] = 0.0f;
	}
}

Arthas::KeyState Arthas::InputManager::getKeyState(KeyCode keyCode)
{
	_ASSERT(keyCode >= 0 && keyCode < MAX_KEY_NUM);
	
	if (keyCode >= MAX_KEY_NUM || keyCode < 0)
		return KS_NONE;

	adjustKeyState(keyCode);

	return m_KeyStates[keyCode];
}

void Arthas::InputManager::getKeyStates(OUT KeyState* keyStates)
{
	_ASSERT(!keyStates);
	if (keyStates == nullptr)
		return;

	for (int i = 0; i < MAX_KEY_NUM; i++)
	{
		adjustKeyState((KeyCode)i);
		keyStates[i] = m_KeyStates[i];
	}
}

void Arthas::InputManager::receiveKeyboardData(cocos2d::Layer* layer)
{
	auto sentinel = Arthas::InputSentinel::create();

	layer->addChild(sentinel);
}

void Arthas::InputSentinel::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	timeval nowTime = GET_GAME_MANAGER()->getTime();

	GET_INPUT_MANAGER()->m_KeyStates[(int)keyCode] = KS_PRESS;
	GET_INPUT_MANAGER()->m_KeyTime[(int)keyCode] = nowTime.tv_usec + nowTime.tv_sec * 1000;
}

void Arthas::InputSentinel::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	timeval nowTime = GET_GAME_MANAGER()->getTime();

	GET_INPUT_MANAGER()->m_KeyStates[(int)keyCode] = KS_RELEASE;
	GET_INPUT_MANAGER()->m_KeyTime[(int)keyCode] = nowTime.tv_usec + nowTime.tv_sec * 1000;
}

void Arthas::InputManager::adjustKeyState(KeyCode keyCode)
{
	timeval nowTime = GET_GAME_MANAGER()->getTime();
	int	timeUsec = nowTime.tv_usec + nowTime.tv_sec * 1000;

	
	if (timeUsec - m_KeyTime[keyCode] > 20)
	{
		if (m_KeyStates[keyCode] == KS_PRESS)
		{
			m_KeyStates[keyCode] = KS_HOLD;
		}
		if (m_KeyStates[keyCode] == KS_RELEASE)
		{
			m_KeyStates[keyCode] = KS_NONE;
		}
	}
}

void Arthas::InputManager::receiveMouseData(cocos2d::Layer* layer)
{
	auto sentinel = Arthas::InputSentinel::create();

	layer->addChild(sentinel);

}

void Arthas::InputSentinel::onMouseDown(cocos2d::Event* event)
{

}

void Arthas::InputSentinel::onMouseUp(cocos2d::Event* event)
{

}

void Arthas::InputSentinel::onMouseMove(cocos2d::Event* event)
{

}

bool Arthas::InputSentinel::init()
{
	auto keyListener = cocos2d::EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(InputSentinel::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(InputSentinel::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	auto mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(InputSentinel::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(InputSentinel::onMouseUp, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(InputSentinel::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;

}