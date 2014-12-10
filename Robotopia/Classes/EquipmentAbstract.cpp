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

void EquipmentAbstract::setEquipmentSprite(cocos2d::Sprite* front, cocos2d::Sprite* frontOutLine, cocos2d::Sprite* inGameSprite)
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

void EquipmentAbstract::setEquipmentIcon(IconState iconState)
{
	m_Icon->changeIconState(iconState);
}

IconState EquipmentAbstract::getEquipmentIconState()
{
	return m_Icon->getIconState();
}

IconLayer* EquipmentAbstract::getEquipmentIcon()
{
	return m_Icon;
}


EquipmentInfo::EquipmentInfo(const EquipmentInfo& other)
{
	m_EquipmentType = other.m_EquipmentType;
	m_Type = other.m_Type;
	m_FrontSprite = other.m_FrontSprite;
	m_FrontOutline = other.m_FrontOutline;
	m_IconSprite = other.m_IconSprite;

	m_Level = other.m_Level;
	m_IsLock = other.m_IsLock;
	m_KWatt = other.m_KWatt;
	m_Level = other.m_Level;
	m_UpgradePrice = other.m_UpgradePrice;
}

EquipmentInfo::EquipmentInfo()
{

}

EquipmentInfo* EquipmentInfo::clone()
{
	return new EquipmentInfo(*this);
}
