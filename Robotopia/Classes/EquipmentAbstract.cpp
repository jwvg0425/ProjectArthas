#include "pch.h"
#include "EquipmentAbstract.h"
#include "IconLayer.h"
bool EquipmentAbstract::init()
{
	if (!ItemAbstract::init())
	{
		return false;
	}

	return true;
}

void EquipmentAbstract::setEquipmentSprite(cocos2d::Sprite* front, cocos2d::Sprite* frontOutLine,
												 cocos2d::Sprite* inGameSprite)
{
	m_Front = front;
	m_FrontOutLine = frontOutLine;
	m_InGameSprite = inGameSprite;
}

void EquipmentAbstract::setEquipmentDescription(std::string description)
{
	m_Description = description;
}

void EquipmentAbstract::update(float dTime)
{
}

void EquipmentAbstract::enter()
{
}

void EquipmentAbstract::exit()
{
}

bool EquipmentAbstract::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentAbstract::setEquipment()
{

}

void EquipmentAbstract::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

void EquipmentAbstract::setEquipmentIcon(IconType iconType, cocos2d::Sprite* iconSprite, cocos2d::Point parentAnchorPoint, cocos2d::Point iconPosition)
{

}




