#include "pch.h"
#include "ButtonLayer.h"
#include "InputManager.h"
#include "ResourceManager.h"


ButtonLayer::ButtonLayer()
{

}

ButtonLayer::~ButtonLayer()
{

}

bool ButtonLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_ButtonType = NO_BUTTON;
	m_ButtonSprite = nullptr;
	return true;
}

void ButtonLayer::update(float dTime)
{
	if (m_ButtonType != NO_BUTTON)
	{
		MouseInfo mouseInput = GET_INPUT_MANAGER()->getMouseInfo();
		if (m_ButtonRect.containsPoint(mouseInput.mouseMove))
		{
			setButtonOver(true);
		}
		else
		{
			setButtonOver(false);
		}
	}
}

void ButtonLayer::setButtonProperties(ButtonType buttonType, cocos2d::Point buttonPosition, std::string buttonLabel, int buttonValue)
{
	m_ButtonType = buttonType;
	m_ButtonValue = buttonValue;
	switch (m_ButtonType)
	{
	case NO_BUTTON:
		break;
	case TITLEMENU_BUTTON:
		break;
	case OPTION_BUTTON:
		break;
	case GAMEMENU_BUTTON:
		m_ButtonSprite = GET_RESOURCE_MANAGER()->createSprite(ST_GAMEMENU_BUTTON_DEFAULT);
		break;
	}
	setUIProperties(m_ButtonSprite, cocos2d::Point(0.5, 0.5), buttonPosition, 0.75f, true, 52);
	this->addChild(m_ButtonSprite);
	getButtonRect(buttonPosition);
}

void ButtonLayer::setButtonOver(bool onButton)
{
	switch (m_ButtonType)
	{
	case NO_BUTTON:
		break;
	case TITLEMENU_BUTTON:
		break;
	case OPTION_BUTTON:
		break;
	case GAMEMENU_BUTTON:
		if (onButton)
		{
			m_ButtonSprite->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GAMEMENU_BUTTON_SELECT)->getTexture());
		}
		else
		{
			m_ButtonSprite->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GAMEMENU_BUTTON_DEFAULT)->getTexture());
		}
		break;
	}

}

void ButtonLayer::getButtonRect(cocos2d::Point buttonPosition)
{
	m_ButtonRect.setRect(m_ButtonSprite->getPosition().x - ((m_ButtonSprite->getContentSize().width * RESOLUTION) / 2), buttonPosition.y, m_ButtonSprite->getContentSize().width * RESOLUTION, m_ButtonSprite->getContentSize().height * RESOLUTION);
}

