#include "pch.h"
#include "EquipmentSteamContainer.h"

bool EquipmentSteamContainer::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}

	return true;
}

void EquipmentSteamContainer::update(float dTime)
{
}

void EquipmentSteamContainer::enter()
{
}

void EquipmentSteamContainer::exit()
{
}

bool EquipmentSteamContainer::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentSteamContainer::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}


void EquipmentSteamContainer::setEquipment(EquipmentType equipmentType, SteamContainerList steamContainerType, 
										   int level, int kWatt, int upgradePrice, bool isLock, 
										   float maxSteam, float AbsorbEffectiveness)
{
	m_SteamContainerInfo.m_EquipmentType = equipmentType;
	m_SteamContainerInfo.m_SteamContainerType = steamContainerType;
	m_SteamContainerInfo.m_Level = level;
	m_SteamContainerInfo.m_KWatt = kWatt;
	m_SteamContainerInfo.m_UpgradePrice = upgradePrice;
	m_SteamContainerInfo.m_IsLock = isLock;
	m_SteamContainerInfo.m_MaxSteam = maxSteam;
	m_SteamContainerInfo.m_AbsorbEffectiveness = AbsorbEffectiveness;
}

