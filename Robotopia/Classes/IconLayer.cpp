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

	m_DragOn = false;
	m_Labeled = false;
	m_Selected = false;
	m_Clicked = false;
	m_Locked = false;
	
	m_IconFrameDefault = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_DEFAULT);
	m_IconFrameClicked = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_CLICKED);
	m_IconFrameSelected = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_SELECTED);
	m_IconFrameLocked = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_LOCKED);
	//if not set icon content, it will show default icon
	m_IconContent = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_CONTENT_DEFAULT);

	m_IconFrameClicked->setVisible(false);
	m_IconFrameSelected->setVisible(false);
	m_IconFrameLocked->setVisible(false);
	m_IconLabel = LabelLayer::create();
	m_IconLabel->setVisible(false);

	m_PrevPoint = cocos2d::Point::ZERO;

	this->addChild(m_IconFrameDefault);
	this->addChild(m_IconFrameSelected);
	this->addChild(m_IconFrameLocked);
	this->addChild(m_IconFrameClicked);
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
	m_IconFrameClicked->setPosition(iconPosition);
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

void IconLayer::createIconLabel(cocos2d::Point iconPosition, bool isLocked)
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
	case ICON_CLICKED:
		changeIconClicked();
		break;
	case ICON_LOCKED:
		changeIconLocked();
		break;
	}
}

void IconLayer::changeIconDefault()
{
	m_IconFrameDefault->setVisible(true);
	m_IconFrameClicked->setVisible(false);
	m_IconFrameSelected->setVisible(false);
	m_IconFrameLocked->setVisible(false);
	m_IconState = ICON_DEFAULT;
	m_Clicked = false;
	m_Selected = false;
}

void IconLayer::changeIconClicked()
{
	m_IconFrameDefault->setVisible(false);
	m_IconFrameClicked->setVisible(true);
	m_IconFrameSelected->setVisible(false);
	m_IconFrameLocked->setVisible(false);
	m_IconState = ICON_CLICKED;
	m_Clicked = true;
}

void IconLayer::changeIconSelected()
{
	m_IconFrameDefault->setVisible(false);
	m_IconFrameClicked->setVisible(false);
	m_IconFrameSelected->setVisible(true);
	m_IconFrameLocked->setVisible(false);
	m_IconState = ICON_SELECTED;
	m_Selected = true;
}

void IconLayer::changeIconLocked()
{
	m_IconFrameDefault->setVisible(false);
	m_IconFrameClicked->setVisible(false);
	m_IconFrameSelected->setVisible(false);
	m_IconFrameLocked->setVisible(true);
	m_IconContent->setVisible(false);
	m_IconState = ICON_LOCKED;
	m_Labeled = true;
}

void IconLayer::doubleClickCheck(cocos2d::Point mouseClickPoint)
{
	if (m_IconState != ICON_LOCKED)
	{
		if (m_IconRect.containsPoint(mouseClickPoint))
		{
			if (m_Selected == false)
			{
				changeIconSelected();
			}
			else if (m_Selected == true)
			{
				changeIconDefault();
			}
		}
	}
}

void IconLayer::clickCheck(cocos2d::Point mouseClickPoint)
{
	if (m_IconState != ICON_LOCKED)
	{
		if (m_IconRect.containsPoint(mouseClickPoint))
		{
			if (m_IconState == ICON_DEFAULT)
			{
				changeIconClicked();
			}
			//셀렉트도 선택 가능하게 바꾸기
		}
	}
}


void IconLayer::hideLabel()
{
	m_IconLabel->setVisible(false);
}

void IconLayer::setIconContent(cocos2d::Sprite* contentIcon)
{
	m_IconContent = contentIcon;
}

IconState IconLayer::getIconState()
{
	return m_IconState;
}

bool IconLayer::getIconSelected()
{
	return m_Selected;
}

bool IconLayer::getIconClicked()
{
	return m_Clicked;
}

bool IconLayer::getIconLocked()
{
	return m_Locked;
}
