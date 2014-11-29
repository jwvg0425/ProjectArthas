#include "pch.h"
#include "EquipmentAbstract.h"
#include "IconLayer.h"

bool EquipmentAbstract::init()
{
	if (!ItemAbstract::init())
	{
		return false;
	}
	m_Icon = nullptr;

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
	if (m_Icon != nullptr)
	{
		m_Icon->update(dTime);
	}
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

void EquipmentAbstract::setEquipmentIcon(IconType iconType, cocos2d::Sprite* iconSprite)
{
	m_Icon = IconLayer::create();
	m_Icon->setIconProperties(iconType, iconSprite);
	this->addChild(m_Icon);
}

IconLayer* EquipmentAbstract::getEquipmentIcon()
{
	return m_Icon;
}
