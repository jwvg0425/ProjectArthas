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
	m_Selected = false;
	m_Locked = false;

	m_IconType = NO_ICON;
	m_IconLabel = LabelLayer::create();
	m_IconFrame = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_DEFAULT);
	m_IconContents = nullptr;
	m_PrevPoint = cocos2d::Point::ZERO;
	
	m_IconLabel->setVisible(false);
	
	this->addChild(m_IconLabel);
	return true;
}

void IconLayer::update(float dTime)
{
	if (m_IconType != NO_ICON)
	{
		MouseInfo mouseInput = GET_INPUT_MANAGER()->getMouseInfo();
		if (m_Locked == false)
		{
			if (m_IconRect.containsPoint(mouseInput.m_MouseStart[LEFT_CLICK_POINT]) && m_IconRect.containsPoint(mouseInput.m_MouseEnd[LEFT_CLICK_POINT]) && mouseInput.m_DoubleClick)
			{
				if (m_Selected)
				{
					setIconDefault();
					GET_INPUT_MANAGER()->resetMouseInfo();
				}
				else
				{
					setIconSelect();
					GET_INPUT_MANAGER()->resetMouseInfo();
				}
			}
			if (m_IconRect.containsPoint(mouseInput.m_MouseStart[LEFT_CLICK_POINT]))
			{
				m_PrevPoint = cocos2d::Point(m_IconFrame->getBoundingBox().getMidX(), m_IconFrame->getBoundingBox().getMidY());
				m_DragOn = true;
			}
// 			if (m_DragOn)
// 			{
// 				if (mouseInput.m_MouseState == MS_LEFT_UP)
// 				{
// 					m_DragOn = false;
// 					GET_INPUT_MANAGER()->resetMouseInfo();
// 				}
// 			}
		}
		
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

void IconLayer::setIconProperties(IconType iconType, cocos2d::Sprite* iconSprite)
{
	m_IconType = iconType;
	m_IconContents = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_DEFAULT);
	m_IconContents->setTexture(iconSprite->getTexture());
	m_IconLabel->setLabelProperties(ASSEMBLY_LABEL);
	this->addChild(m_IconFrame);
	this->addChild(m_IconContents);
}

void IconLayer::setIconRect(cocos2d::Point parentAnchorPoint, cocos2d::Point iconPosition)
{
	m_IconFrame->setPosition(iconPosition);
	m_IconContents->setPosition(iconPosition);
	cocos2d::Rect tempRect = m_IconFrame->getBoundingBox();
	m_IconRect.setRect(parentAnchorPoint.x + tempRect.getMinX() * RESOLUTION, parentAnchorPoint.y + tempRect.getMinY() * RESOLUTION,
		m_IconFrame->getContentSize().width * RESOLUTION, m_IconFrame->getContentSize().height * RESOLUTION);

	m_IconLabel->setLabelRect(iconPosition, true);
}

void IconLayer::setIconDefault()
{
	m_IconFrame->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_DEFAULT)->getTexture());
	m_IconContents->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_DEFAULT)->getTexture());
	m_Selected = false;
}

void IconLayer::setIconSelect()
{
	m_IconFrame->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_SELECT)->getTexture());
	m_IconContents->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_SELECT)->getTexture());
	m_Selected = true;
}

void IconLayer::setIconLocked()
{
	m_IconFrame->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_FRAME_DEFAULT)->getTexture());
	m_IconContents->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_ICON_LOCKED)->getTexture());
	m_Locked = true;
}

bool IconLayer::getSelected()
{
	return m_Selected;
}

