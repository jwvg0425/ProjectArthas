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

void ButtonLayer::setButtonProperties(ButtonType buttonType, cocos2d::Point parentAnchorPoint, cocos2d::Point buttonPosition, std::string buttonLabel, int buttonValue)
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
	m_ButtonLabel = cocos2d::Label::create(buttonLabel, "Helvetica", 30 * RESOLUTION);
	m_ButtonLabel->setPosition(cocos2d::Point(m_ButtonSprite->getContentSize().width / 2, m_ButtonSprite->getContentSize().height / 2));
	//m_ButtonLabel->setTextColor(cocos2d::Color4B(74, 255, 246, 0));
	//색깔을 어떻게 바꾸지???
	m_ButtonSprite->setPosition(buttonPosition);

	m_ButtonSprite->addChild(m_ButtonLabel);
	this->addChild(m_ButtonSprite);

	setButtonRect(parentAnchorPoint);
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

void ButtonLayer::setButtonRect(cocos2d::Point parentAnchorPoint)
{
	cocos2d::Rect tempRect = m_ButtonSprite->getBoundingBox();
	m_ButtonRect.setRect(parentAnchorPoint.x + tempRect.getMinX() * RESOLUTION, parentAnchorPoint.y + tempRect.getMinY() * RESOLUTION,
						m_ButtonSprite->getContentSize().width * RESOLUTION, m_ButtonSprite->getContentSize().height * RESOLUTION);
}

