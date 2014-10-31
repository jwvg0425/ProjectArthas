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
}

Arthas::KeyState Arthas::InputManager::getKeyState(KeyCode keyCode)
{
	_ASSERT(keyCode >= 0 && keyCode < MAX_KEY_NUM);
	
	if (keyCode >= MAX_KEY_NUM || keyCode < 0)
		return KS_NONE;

	return m_KeyStates[keyCode];
}

void Arthas::InputManager::getKeyStates(OUT KeyState* keyStates)
{
	_ASSERT(!keyStates);
	if (keyStates == nullptr)
		return;

	for (int i = 0; i < MAX_KEY_NUM; i++)
	{
		keyStates[i] = m_KeyStates[i];
	}
}

void Arthas::InputManager::receiveKeyboardData(cocos2d::EventDispatcher* eventDispatcher, cocos2d::Node* receiver)
{
	_ASSERT(!eventDispatcher && !receiver);

	if (eventDispatcher == nullptr || receiver == nullptr)
		return;

	auto keyListener = cocos2d::EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(InputManager::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(InputManager::onKeyReleased, this);
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
}

void Arthas::InputManager::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	m_KeyStates[(int)keyCode] = KS_HOLD;
}

void Arthas::InputManager::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	m_KeyStates[(int)keyCode] = KS_NONE;
}

