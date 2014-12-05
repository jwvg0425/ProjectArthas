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
	m_Front = other.m_Front;
	m_Icon = other.m_Icon;
	m_IsLock = other.m_IsLock;
	m_KWatt = other.m_KWatt;
	m_Level = other.m_Level;
}

EquipmentInfo::EquipmentInfo()
{

}

EquipmentInfo* EquipmentInfo::clone()
{
	return new EquipmentInfo(*this);
}
