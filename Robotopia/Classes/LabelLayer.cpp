#include "pch.h"
#include "LabelLayer.h"
#include "ResourceManager.h"

bool LabelLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	m_LabelType = NO_LABEL;
	m_LabelFrame = nullptr;
	m_LabelWidth = 0.0f;
	m_LabelHeight = 0.0f;
	return true;
}

void LabelLayer::update(float dTime)
{

}

void LabelLayer::setLabelProperties(LabelType labelType, cocos2d::Point anchorPoint, cocos2d::Point labelPosition)
{
	switch (labelType)
	{
	case ASSEMBLY_LABEL:
		m_LabelFrame = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_LABEL_FRAME);
		m_LabelFrame->setAnchorPoint(anchorPoint);
		m_LabelFrame->setPosition(labelPosition);
		m_LabelFrame->setGlobalZOrder(100);
		break;
	case CHARWIN_LABEL:
		break;
	}
	this->addChild(m_LabelFrame);
}
