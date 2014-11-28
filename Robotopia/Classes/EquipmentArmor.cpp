#include "pch.h"
#include "EquipmentArmor.h"

bool EquipmentArmor::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}

	return true;
}

void EquipmentArmor::update(float dTime)
{
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

void EquipmentArmor::setEquipment(EquipmentType equipmentType, ArmorList engineType,
								   int level, int kWatt, int upgradePrice, bool isLock,
								   float defensivePower, float antiSlow)
{
	m_ArmorInfo.m_EquipmentType = equipmentType;
	m_ArmorInfo.m_EngineType = engineType;
	m_ArmorInfo.m_Level = level;
	m_ArmorInfo.m_KWatt = kWatt;
	m_ArmorInfo.m_UpgradePrice = upgradePrice;
	m_ArmorInfo.m_IsLock = isLock;
	m_ArmorInfo.m_DefensivePower = defensivePower;
	m_ArmorInfo.m_AntiSlow = antiSlow;
}

