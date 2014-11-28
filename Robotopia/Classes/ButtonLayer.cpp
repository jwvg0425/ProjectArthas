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
		if (m_ButtonRect.containsPoint(mouseInput.m_MouseMove))
		{
			setButtonOver(true);
		}
		else
		{
			setButtonOver(false);
		}

		if (m_ButtonRect.containsPoint(mouseInput.m_MouseStart[LEFT_CLICK_POINT]) && m_ButtonRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]))
		{
			GET_INPUT_MANAGER()->resetMouseInfo();
			m_Callback();
		}
	}
}

void ButtonLayer::setButtonProperties(ButtonType buttonType, cocos2d::Point parentAnchorPoint, cocos2d::Point buttonPosition, std::string buttonLabel)
{
	m_ButtonType = buttonType;
	switch (m_ButtonType)
	{
	case NO_BUTTON:
		break;
	case TITLEMENU_BUTTON:
		break;
	case OPTION_BUTTON:
		break;
	case ASSEMBLY_BUTTON:
		m_ButtonSprite = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_BUTTON_DEFAULT);
		break;
	case GAMEMENU_BUTTON:
		m_ButtonSprite = GET_RESOURCE_MANAGER()->createSprite(ST_GAMEMENU_BUTTON_DEFAULT);
		break;
	}
	m_ButtonLabel = cocos2d::Label::createWithSystemFont(buttonLabel, "Calibri", 40 * RESOLUTION);
	m_ButtonLabel->setPosition(cocos2d::Point(m_ButtonSprite->getContentSize().width / 2, m_ButtonSprite->getContentSize().height / 2));

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
	case ASSEMBLY_BUTTON:
		if (onButton)
		{
			m_ButtonSprite->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_BUTTON_SELECT)->getTexture());
		}
		else
		{
			m_ButtonSprite->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_BUTTON_DEFAULT)->getTexture());
		}
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

void ButtonLayer::setButtonFunc(std::function<void()> buttonCallback)
{
	m_Callback = buttonCallback;
}

