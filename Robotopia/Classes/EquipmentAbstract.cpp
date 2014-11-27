#include "pch.h"
#include "EquipmentAbstract.h"

bool EquipmentAbstract::init()
{
	if (!ItemAbstract::init())
	{
		return false;
	}

	return true;
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

void EquipmentAbstract::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

void EquipmentAbstract::setEquipment()
{
}


void EquipmentAbstract::setEquipmentSpr(cocos2d::Sprite* front, cocos2d::Sprite* frontOutLine,
												 cocos2d::Sprite* inGameSprite, cocos2d::Sprite* icon,
												 cocos2d::Sprite* m_DescriptionBackground)
{
	if (front == nullptr || frontOutLine == nullptr
		|| inGameSprite == nullptr || icon == nullptr)
	{
		return;
	}

	m_Front = front;
	m_FrontOutLine = frontOutLine;
	m_InGameSprite = inGameSprite;
	m_Icon = icon;
	m_DescriptionBackground = m_DescriptionBackground;
}

void EquipmentAbstract::setEquipmentDescription(std::string description)
{
	m_Description = description;
}
