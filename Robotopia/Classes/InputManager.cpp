#include "pch.h"
#include "GameManager.h"
#include "InputManager.h"

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

bool InputManager::init()
{
	initKeyState();
	initMouseState();
	return true;
}

void InputManager::initKeyState()
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

KeyState InputManager::getKeyState(KeyCode keyCode)
{
	_ASSERT(keyCode >= 0 && keyCode < MAX_KEY_NUM);
	
	if (keyCode >= MAX_KEY_NUM || keyCode < 0)
		return KS_NONE;

	adjustKeyState(keyCode);

	return m_KeyStates[keyCode];
}

void InputManager::getKeyStates(OUT KeyState* keyStates)
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

void InputManager::receiveKeyboardData(cocos2d::Layer* layer)
{
	auto sentinel = InputSentinel::create();

	layer->addChild(sentinel);
}

void InputSentinel::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	timeval nowTime = GET_GAME_MANAGER()->getTime();

	GET_INPUT_MANAGER()->m_KeyStates[(int)keyCode] = KS_PRESS;
	GET_INPUT_MANAGER()->m_KeyTime[(int)keyCode] = nowTime.tv_usec / 1000 + nowTime.tv_sec * 1000;
}

void InputSentinel::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	timeval nowTime = GET_GAME_MANAGER()->getTime();

	GET_INPUT_MANAGER()->m_KeyStates[(int)keyCode] = KS_RELEASE;
	GET_INPUT_MANAGER()->m_KeyTime[(int)keyCode] = nowTime.tv_usec / 1000 + nowTime.tv_sec * 1000;
}

void InputManager::adjustKeyState(KeyCode keyCode)
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
	m_MouseInfo.m_DragOn = false;
	m_MouseInfo.m_DoubleClick = false;
	m_MouseInfo.m_MouseState = MS_NONE;
	for (int i = 0; i < MOUSEBUTTON; ++i)
	{
		m_MouseInfo.m_MouseStart[i] = cocos2d::Point(INFINITE + 0.0f, INFINITE + 0.0f);
		m_MouseInfo.m_MouseEnd[i] = cocos2d::Point(INFINITE + 0.0f, INFINITE + 0.0f);
	}
	m_MouseInfo.m_MouseMove = cocos2d::Point(INFINITE + 0.0f, INFINITE + 0.0f);
	m_MouseTime = 0;
}

MouseInfo InputManager::getMouseInfo()
{
	return m_MouseInfo;
}

// 더블클릭 고장 / 시간을 받아올 수 없음
void InputManager::checkDoubleClick()
{
	//GetTickCount();
	timeval currentTime = GET_GAME_MANAGER()->getTime();
	cocos2d::log("currentTime: %f", currentTime);
	int	timeUsec = currentTime.tv_usec / 1000 + currentTime.tv_sec * 1000;
	cocos2d::log("m_MouseTimeBefore: %f", m_MouseTime);
	cocos2d::log("timeUsec: %f", timeUsec);
	if (timeUsec - m_MouseTime < 500)
	{
		m_MouseInfo.m_DoubleClick = true;
	}
	m_MouseTime = currentTime.tv_usec / 1000 + currentTime.tv_sec * 1000;
	cocos2d::log("m_MouseTimeAfter: %f", m_MouseTime);
}

void InputManager::resetMouseInfo()
{
	m_MouseInfo.m_DoubleClick = false;
	m_MouseInfo.m_MouseState = MS_NONE;
	for (int i = 0; i < MOUSEBUTTON; ++i)
	{
		m_MouseInfo.m_MouseStart[i] = cocos2d::Point(INFINITE + 0.0f, INFINITE + 0.0f);
		m_MouseInfo.m_MouseEnd[i] = cocos2d::Point(INFINITE + 0.0f, INFINITE + 0.0f);
	}
	m_MouseInfo.m_ScollValue = 0;
	cocos2d::log("mouse RESET!@!!");
}

void InputManager::receiveMouseData(cocos2d::Layer* layer)
{
	auto sentinel = InputSentinel::create();
	layer->addChild(sentinel);
}

void InputSentinel::onMouseDown(cocos2d::Event* event)
{
	auto ev = static_cast<cocos2d::EventMouse*>(event);
	auto button = ev->getMouseButton();
	if (button == MOUSE_BUTTON_LEFT)
	{
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseState = MS_LEFT_DOWN;
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseStart[LEFT_CLICK_POINT].x = ev->getCursorX();
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseStart[LEFT_CLICK_POINT].y = GET_INPUT_MANAGER()->m_WinHeight + ev->getCursorY();
		GET_INPUT_MANAGER()->m_MouseInfo.m_DragOn = true;
		GET_INPUT_MANAGER()->checkDoubleClick();	
		cocos2d::log("mouse down!");
	}
	else if (button == MOUSE_BUTTON_RIGHT)
	{
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseState = MS_RIGHT_DOWN;
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseStart[RIGHT_CLICK_POINT].x = ev->getCursorX();
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseStart[RIGHT_CLICK_POINT].y = GET_INPUT_MANAGER()->m_WinHeight + ev->getCursorY();
	}
}

void InputSentinel::onMouseUp(cocos2d::Event* event)
{
	auto ev = static_cast<cocos2d::EventMouse*>(event);
	auto button = ev->getMouseButton();
	if (button == MOUSE_BUTTON_LEFT)
	{
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseState = MS_LEFT_UP;
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseEnd[LEFT_CLICK_POINT].x = ev->getCursorX();
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseEnd[LEFT_CLICK_POINT].y = GET_INPUT_MANAGER()->m_WinHeight + ev->getCursorY();
		GET_INPUT_MANAGER()->m_MouseInfo.m_DragOn = false;
	}
	else if (button == MOUSE_BUTTON_RIGHT)
	{
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseState = MS_RIGHT_UP;
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseEnd[RIGHT_CLICK_POINT].x = ev->getCursorX();
		GET_INPUT_MANAGER()->m_MouseInfo.m_MouseEnd[RIGHT_CLICK_POINT].y = GET_INPUT_MANAGER()->m_WinHeight + ev->getCursorY();
	}
}

void InputSentinel::onMouseMove(cocos2d::Event* event)
{
	auto ev = static_cast<cocos2d::EventMouse*>(event);
	GET_INPUT_MANAGER()->m_MouseInfo.m_MouseMove.x = ev->getCursorX();
	GET_INPUT_MANAGER()->m_MouseInfo.m_MouseMove.y = GET_INPUT_MANAGER()->m_WinHeight + ev->getCursorY();
}

void InputSentinel::onMouseScroll(cocos2d::Event* event)
{
	auto ev = static_cast<cocos2d::EventMouse*>(event);
	GET_INPUT_MANAGER()->m_MouseInfo.m_ScollValue = ev->getScrollY();
}

bool InputSentinel::init()
{
	if (!Node::init())
	{
		return false;
	}

	auto keyListener = cocos2d::EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(InputSentinel::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(InputSentinel::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	auto mouseListener = cocos2d::EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(InputSentinel::onMouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(InputSentinel::onMouseUp, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(InputSentinel::onMouseMove, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(InputSentinel::onMouseScroll, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

	return true;
}

