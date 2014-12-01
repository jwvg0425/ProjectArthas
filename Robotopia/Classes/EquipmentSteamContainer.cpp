#include "pch.h"
#include "EquipmentSteamContainer.h"
#include "IconLayer.h"

bool EquipmentSteamContainer::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}
	m_Icon = IconLayer::create();
	this->addChild(m_Icon);
	return true;
}

void EquipmentSteamContainer::update(float dTime)
{
	if (m_Icon != nullptr)
	{
		m_Icon->update(dTime);
	}
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
	
	if (m_SteamContainerInfo.m_IsLock)
	{
		m_Icon->changeIconState(ICON_LOCKED);
	}
}

void EquipmentSteamContainer::setEquipment(SteamContainerInfo steamContainerInfo)
{
	setEquipment(steamContainerInfo.m_EquipmentType, steamContainerInfo.m_SteamContainerType,
				 steamContainerInfo.m_Level, m_SteamContainerInfo.m_KWatt,
				 steamContainerInfo.m_UpgradePrice, steamContainerInfo.m_IsLock,
				 steamContainerInfo.m_MaxSteam, m_SteamContainerInfo.m_AbsorbEffectiveness);
}

EquipmentSteamContainer::SteamContainerInfo EquipmentSteamContainer::getEquipmentInfo()
{
	return m_SteamContainerInfo;
}

