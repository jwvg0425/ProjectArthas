#include "GameManager.h"
#include "InputManager.h"

#define LEFT_CLICK_POINT 0
#define RIGHT_CLICK_POINT 1

BEGIN_NS_AT

Arthas::InputManager::InputManager()
{

}

Arthas::InputManager::~InputManager()
{

}

bool Arthas::InputManager::init()
{
	initKeyState();
	initMouseState();
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
	GET_INPUT_MANAGER()->m_KeyTime[(int)keyCode] = nowTime.tv_usec / 1000 + nowTime.tv_sec * 1000;
}

void Arthas::InputSentinel::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	timeval nowTime = GET_GAME_MANAGER()->getTime();

	GET_INPUT_MANAGER()->m_KeyStates[(int)keyCode] = KS_RELEASE;
	GET_INPUT_MANAGER()->m_KeyTime[(int)keyCode] = nowTime.tv_usec / 1000 + nowTime.tv_sec * 1000;
}

void Arthas::InputManager::adjustKeyState(KeyCode keyCode)
{
	timeval nowTime = GET_GAME_MANAGER()->getTime();
	int	timeUsec = nowTime.tv_usec/1000 + nowTime.tv_sec * 1000;
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

void InputManager::initMouseState()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;
	//MouseInfo Clear
	m_MouseInfo.dragOn = false;
	m_MouseInfo.doubleClick = false;
	m_MouseInfo.mouseState = MS_NONE;
	for (int i = 0; i < MOUSEBUTTON; ++i)
	{
		m_MouseInfo.mouseStart[i] = cocos2d::Point(INFINITE + 0.0f, INFINITE + 0.0f);
		m_MouseInfo.mouseEnd[i] = cocos2d::Point(INFINITE + 0.0f, INFINITE + 0.0f);
	}
	m_MouseInfo.mouseMove = cocos2d::Point(INFINITE + 0.0f, INFINITE + 0.0f);
	m_MouseTime = 0;
}

Arthas::MouseInfo InputManager::getMouseInfo()
{
	return m_MouseInfo;
}

void InputManager::checkDoubleClick()
{
	timeval currentTime = GET_GAME_MANAGER()->getTime();
	int	timeUsec = currentTime.tv_usec / 1000 + currentTime.tv_sec * 1000;
	if (timeUsec - m_MouseTime < 250)
	{
		m_MouseInfo.doubleClick = true;
	}
}

void InputManager::resetMouseInfo()
{
	m_MouseInfo.mouseState = MS_NONE;
	m_MouseInfo.doubleClick = false;
}

void Arthas::InputManager::receiveMouseData(cocos2d::Layer* layer)
{
	auto sentinel = Arthas::InputSentinel::create();
	layer->addChild(sentinel);
}

void Arthas::InputSentinel::onMouseDown(cocos2d::Event* event)
{
	auto ev = static_cast<cocos2d::EventMouse*>(event);
	auto button = ev->getMouseButton();
	if (button == MOUSE_BUTTON_LEFT)
	{
		GET_INPUT_MANAGER()->m_MouseInfo.mouseState = MS_LEFT_DOWN;
		GET_INPUT_MANAGER()->m_MouseInfo.mouseStart[LEFT_CLICK_POINT].x = ev->getCursorX();
		GET_INPUT_MANAGER()->m_MouseInfo.mouseStart[LEFT_CLICK_POINT].y = GET_INPUT_MANAGER()->m_WinHeight + ev->getCursorY();
		GET_INPUT_MANAGER()->m_MouseInfo.dragOn = true;
		GET_INPUT_MANAGER()->checkDoubleClick();
		timeval currentTime = GET_GAME_MANAGER()->getTime();
		GET_INPUT_MANAGER()->m_MouseTime = currentTime.tv_usec / 1000 + currentTime.tv_sec * 1000;
		
	}
	else if (button == MOUSE_BUTTON_RIGHT)
	{
		GET_INPUT_MANAGER()->m_MouseInfo.mouseState = MS_RIGHT_DOWN;
		GET_INPUT_MANAGER()->m_MouseInfo.mouseStart[RIGHT_CLICK_POINT].x = ev->getCursorX();
		GET_INPUT_MANAGER()->m_MouseInfo.mouseStart[RIGHT_CLICK_POINT].y = GET_INPUT_MANAGER()->m_WinHeight + ev->getCursorY();
	}
}

void Arthas::InputSentinel::onMouseUp(cocos2d::Event* event)
{
	auto ev = static_cast<cocos2d::EventMouse*>(event);
	auto button = ev->getMouseButton();
	if (button == MOUSE_BUTTON_LEFT)
	{
		GET_INPUT_MANAGER()->m_MouseInfo.mouseState = MS_LEFT_UP;
		GET_INPUT_MANAGER()->m_MouseInfo.mouseEnd[LEFT_CLICK_POINT].x = ev->getCursorX();
		GET_INPUT_MANAGER()->m_MouseInfo.mouseEnd[LEFT_CLICK_POINT].y = GET_INPUT_MANAGER()->m_WinHeight + ev->getCursorY();
		GET_INPUT_MANAGER()->m_MouseInfo.dragOn = false;
	}
	else if (button == MOUSE_BUTTON_RIGHT)
	{
		GET_INPUT_MANAGER()->m_MouseInfo.mouseState = MS_RIGHT_UP;
		GET_INPUT_MANAGER()->m_MouseInfo.mouseEnd[RIGHT_CLICK_POINT].x = ev->getCursorX();
		GET_INPUT_MANAGER()->m_MouseInfo.mouseEnd[RIGHT_CLICK_POINT].y = GET_INPUT_MANAGER()->m_WinHeight + ev->getCursorY();
	}
}

void Arthas::InputSentinel::onMouseMove(cocos2d::Event* event)
{
	auto ev = static_cast<cocos2d::EventMouse*>(event);
	GET_INPUT_MANAGER()->m_MouseInfo.mouseMove.x = ev->getCursorX();
	GET_INPUT_MANAGER()->m_MouseInfo.mouseMove.y = GET_INPUT_MANAGER()->m_WinHeight + ev->getCursorY();
}

bool Arthas::InputSentinel::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto keyListener = cocos2d::EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(Arthas::InputSentinel::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(Arthas::InputSentinel::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	auto mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(Arthas::InputSentinel::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(Arthas::InputSentinel::onMouseUp, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(Arthas::InputSentinel::onMouseMove, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

END_NS_AT