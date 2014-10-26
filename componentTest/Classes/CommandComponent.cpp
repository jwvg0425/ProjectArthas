#include "CommandComponent.h"
#include "ObserverComponent.h"
#include "Object.h"
#include "KeyboardTrigger.h"


void CommandComponent::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_KeyStates |= KEY_LEFT;
	}

	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_KeyStates |= KEY_RIGHT;
	}
}

void CommandComponent::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_KeyStates &= ~KEY_LEFT;
	}

	if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_KeyStates &= ~KEY_RIGHT;
	}
}

void CommandComponent::update(float dTime)
{
	if (m_KeyStates != 0)
	{
		ObserverComponent* observer = (ObserverComponent*)m_Parent->getComponent(3);

		if (observer != nullptr)
		{
			observer->addTrigger(new KeyboardTrigger(m_KeyStates));
		}
	}
	//m_KeyStates = 0;
}

void CommandComponent::enter()
{

}

void CommandComponent::exit()
{

}

CommandComponent::CommandComponent(Object* parent)
{
	m_Parent = parent;

	m_KeyStates = 0;

	auto keyListener = cocos2d::EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(CommandComponent::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(CommandComponent::onKeyReleased, this);

	m_Parent->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyListener, m_Parent);
}

CommandComponent::~CommandComponent()
{

}
