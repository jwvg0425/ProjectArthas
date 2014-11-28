#include "pch.h"
#include "EquipmentHead.h"
#include "IconLayer.h"

bool EquipmentHead::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}
	m_Icon = nullptr;
	return true;
}

void EquipmentHead::update(float dTime)
{
	if (m_Icon != nullptr)
	{
		m_Icon->update(dTime);
	}
}

void EquipmentHead::enter()
{
}

void EquipmentHead::exit()
{
}

bool EquipmentHead::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentHead::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

void EquipmentHead::setEquipment(EquipmentType equipmentType, HeadList headType, int level, int kWatt, 
								 int upgradePrice, bool isLock, float skillCoolTimeDown, float mainMemory)
{
	m_HeadInfo.m_EquipmentType = equipmentType;
	m_HeadInfo.m_HeadType = headType;
	m_HeadInfo.m_Level = level;
	m_HeadInfo.m_KWatt = kWatt;
	m_HeadInfo.m_UpgradePrice = upgradePrice;
	m_HeadInfo.m_IsLock = isLock;
	m_HeadInfo.m_SkillCoolTimeDown = skillCoolTimeDown;
	m_HeadInfo.m_MainMemory = mainMemory;
}
