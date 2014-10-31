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

void Arthas::InputManager::receiveKeyboardData(cocos2d::EventDispatcher* eventDispatcher)
{
	_ASSERT(!eventDispatcher);

	if (eventDispatcher == nullptr)
		return;

	auto keyListener = cocos2d::EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void Arthas::InputManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	timeval nowTime = GET_GAME_MANAGER()->getTime();

	m_KeyStates[(int)keyCode] = KS_PRESS;
	m_KeyTime[(int)keyCode] = nowTime.tv_usec + nowTime.tv_sec * 1000;
}

void Arthas::InputManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	timeval nowTime = GET_GAME_MANAGER()->getTime();

	m_KeyStates[(int)keyCode] = KS_RELEASE;
	m_KeyTime[(int)keyCode] = nowTime.tv_usec + nowTime.tv_sec * 1000;
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

