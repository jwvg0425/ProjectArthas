#include "pch.h"
#include "LabelLayer.h"
#include "ResourceManager.h"

bool LabelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_LabelWidth = 0.0f;
	m_LabelHeight = 0.0f;
	m_LabelFrame = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_LABEL_FRAME);
	m_LabelFrame->setGlobalZOrder(5);
	this->addChild(m_LabelFrame);
	return true;
}

void LabelLayer::update(float dTime)
{
}

void LabelLayer::setLabelPosition(cocos2d::Point labelPosition, bool rectDirDown)
{
	if (rectDirDown)
	{
		m_LabelFrame->setAnchorPoint(cocos2d::Point(0, 0));
		m_LabelFrame->setPosition(cocos2d::Point(labelPosition.x - 30, labelPosition.y + 30));
	}
	else
	{
		m_LabelFrame->setAnchorPoint(cocos2d::Point(0, 1));
		m_LabelFrame->setPosition(cocos2d::Point(labelPosition.x - 30, labelPosition.y - 30));
	}
}

//라벨 문구와 이미지들이 들어가는 곳
void LabelLayer::setLabelContents(bool isLocked)
{
	if (isLocked)
	{

	}
	else
	{
		m_LabelText = cocos2d::Label::createWithSystemFont("Double click to equip", "Calibri", 25 * RESOLUTION);
		m_LabelFrame->addChild(m_LabelText);
		m_LabelText->setPosition(cocos2d::Point(100, 165));
	}
}
