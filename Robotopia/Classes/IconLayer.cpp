#include "pch.h"
#include "IconLayer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "LabelLayer.h"

bool IconLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	m_WinWidth = winSize.width;
	m_WinHeight = winSize.height;

	m_Selected = false;
	m_Locked = false;
	m_DragOn = false;
	m_Labeled = false;

	m_IconFrameDefault = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_DEFAULT);
	m_IconFrameSelected = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_SELECT);
	m_IconFrameLocked = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_LOCKED);
	m_IconFrameSelected->setVisible(false);
	m_IconFrameLocked->setVisible(false);
	m_IconLabel = LabelLayer::create();
	m_IconLabel->setVisible(false);
	//if not set icon content, it will show default icon
	m_IconContent = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_DEFAULT);
	m_PrevPoint = cocos2d::Point::ZERO;

	this->addChild(m_IconFrameDefault);
	this->addChild(m_IconFrameSelected);
	this->addChild(m_IconFrameLocked);
	this->addChild(m_IconContent);
	this->addChild(m_IconLabel);

	return true;
}

void IconLayer::update(float dTime)
{
	MouseInfo mouseInput = GET_INPUT_MANAGER()->getMouseInfo();
	if (m_Labeled)
	{
		if (m_IconRect.containsPoint(mouseInput.m_MouseMove))
		{
			m_IconLabel->setVisible(true);
		}
		else
		{
			m_IconLabel->setVisible(false);
		}
	}
}

void IconLayer::setIconRect(cocos2d::Point parentAnchorPoint, cocos2d::Point iconPosition)
{
	m_IconFrameDefault->setPosition(iconPosition);
	m_IconFrameLocked->setPosition(iconPosition);
	m_IconFrameSelected->setPosition(iconPosition);
	m_IconContent->setPosition(iconPosition);
	cocos2d::Rect tempRect = m_IconFrameDefault->getBoundingBox();
	m_IconRect.setRect(parentAnchorPoint.x + tempRect.getMinX() * RESOLUTION, parentAnchorPoint.y + tempRect.getMinY() * RESOLUTION,
		m_IconFrameDefault->getContentSize().width * RESOLUTION, m_IconFrameDefault->getContentSize().height * RESOLUTION);
	if (m_Labeled)
	{
		if (m_IconFrameDefault->getBoundingBox().getMinY() > m_WinHeight / 2)
			m_IconLabel->setLabelPosition(iconPosition, true);
		else
			m_IconLabel->setLabelPosition(iconPosition, false);
	}
}

void IconLayer::setIconLabel(cocos2d::Point iconPosition, bool isLocked)
{
	m_IconLabel->setLabelContents(isLocked);
	if (m_IconFrameDefault->getBoundingBox().getMinY() > m_WinHeight / 2)
		m_IconLabel->setLabelPosition(iconPosition, true);
	else
		m_IconLabel->setLabelPosition(iconPosition, false);
	m_Labeled = true;
}

void IconLayer::changeIconState(IconState iconState)
{
	switch (iconState)
	{
	case ICON_DEFAULT:
		changeIconDefault();
		break;
	case ICON_SELECTED:
		changeIconSelected();
		break;
	case ICON_LOCKED:
		changeIconLocked();
		break;
	}
}

void IconLayer::changeIconDefault()
{
	m_IconFrameDefault->setVisible(true);
	m_IconFrameSelected->setVisible(false);
	m_IconFrameLocked->setVisible(false);
	m_Selected = false;
	m_IconState = ICON_DEFAULT;
}

void IconLayer::changeIconSelected()
{
	m_IconFrameDefault->setVisible(false);
	m_IconFrameSelected->setVisible(true);
	m_IconFrameLocked->setVisible(false);
	m_Selected = true;
	m_IconState = ICON_SELECTED;
}

void IconLayer::changeIconLocked()
{
	m_IconFrameDefault->setVisible(false);
	m_IconFrameSelected->setVisible(false);
	m_IconFrameLocked->setVisible(true);
	m_IconContent->setVisible(false);
	m_Locked = true;
	m_IconState = ICON_LOCKED;
}

bool IconLayer::getSelected()
{
	return m_Selected;
}

void IconLayer::setIconContent(cocos2d::Sprite* contentIcon)
{
	m_IconContent = contentIcon;
}

void IconLayer::doubleClickCheck(cocos2d::Point mouseClickPoint)
{
	if (!m_Locked)
	{
		if (m_IconRect.containsPoint(mouseClickPoint))
		{
			if (m_Selected)
			{
				changeIconDefault();
				GET_INPUT_MANAGER()->resetMousePoints();
				GET_INPUT_MANAGER()->resetMouseDoubleClick();
			}
			else
			{
				changeIconSelected();
				GET_INPUT_MANAGER()->resetMousePoints();
				GET_INPUT_MANAGER()->resetMouseDoubleClick();
			}
		}
	}
}

void IconLayer::hideLabel()
{
	m_IconLabel->setVisible(false);
}

bool IconLayer::getClicked()
{
	return m_Clicked;
}
