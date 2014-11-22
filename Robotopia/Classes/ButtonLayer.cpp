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

void ButtonLayer::update()
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

void ButtonLayer::setButtonProperties(ButtonType buttonType, std::string buttonLabel, int buttonValue)
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
	getButtonRect();
}

void ButtonLayer::setButtonOver(bool onButton)
{
	if (onButton)
	{
		m_ButtonSprite->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GAMEMENU_BUTTON_SELECT)->getTexture());
	}
	else
	{
		m_ButtonSprite->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_GAMEMENU_BUTTON_DEFAULT)->getTexture());
	}
}

void ButtonLayer::getButtonRect()
{
	m_ButtonRect.setRect(m_ButtonSprite->getPosition().x, m_ButtonSprite->getPosition().y, m_ButtonSprite->getContentSize().width, m_ButtonSprite->getContentSize().height);
}

