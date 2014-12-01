#include "pch.h"
#include "EquipmentArmor.h"
#include "IconLayer.h"

bool EquipmentArmor::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}
	m_Icon = IconLayer::create();
	this->addChild(m_Icon);
	return true;
}

void EquipmentArmor::update(float dTime)
{
	if (m_Icon != nullptr)
	{
		m_Icon->update(dTime);
	}
}

void EquipmentArmor::enter()
{
}

void EquipmentArmor::exit()
{
}

bool EquipmentArmor::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentArmor::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

void EquipmentArmor::setEquipment(EquipmentType equipmentType, ArmorList armorType,
								   int level, int kWatt, int upgradePrice, bool isLock,
								   float defensivePower, float antiSlow)
{
	m_ArmorInfo.m_EquipmentType = equipmentType;
	m_ArmorInfo.m_ArmorType = armorType;
	m_ArmorInfo.m_Level = level;
	m_ArmorInfo.m_KWatt = kWatt;
	m_ArmorInfo.m_UpgradePrice = upgradePrice;
	m_ArmorInfo.m_IsLock = isLock;
	m_ArmorInfo.m_DefensivePower = defensivePower;
	m_ArmorInfo.m_AntiSlow = antiSlow;

	if (m_ArmorInfo.m_IsLock)
	{
		m_Icon->changeIconState(ICON_LOCKED);
	}
}

void EquipmentArmor::setEquipment(ArmorInfo armorInfo)
{
	setEquipment(armorInfo.m_EquipmentType, armorInfo.m_ArmorType,
				 armorInfo.m_Level,armorInfo.m_KWatt,
				 armorInfo.m_UpgradePrice, armorInfo.m_IsLock, 
				 armorInfo.m_DefensivePower, armorInfo.m_AntiSlow);
}

EquipmentArmor::ArmorInfo EquipmentArmor::getEquipmentInfo()
{
	return m_ArmorInfo;
}

