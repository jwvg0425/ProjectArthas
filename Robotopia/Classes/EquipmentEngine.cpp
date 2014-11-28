#include "pch.h"
#include "EquipmentEngine.h"

bool EquipmentEngine::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}

	return true;
}

void EquipmentEngine::update(float dTime)
{
}

void EquipmentEngine::enter()
{
}

 void EquipmentEngine::exit()
{
}

bool EquipmentEngine::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentEngine::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

void EquipmentEngine::setEquipment(EquipmentType equipmentType, EngineList engineType, 
								   int level, int kWatt, int upgradePrice, bool isLock, 
								   float electronicPower, float steamEffectiveness)
{
	m_EngineInfo.m_EquipmentType = equipmentType;
	m_EngineInfo.m_EngineType = engineType;
	m_EngineInfo.m_Level = level;
	m_EngineInfo.m_KWatt = kWatt;
	m_EngineInfo.m_UpgradePrice = upgradePrice;
	m_EngineInfo.m_IsLock = isLock;
	m_EngineInfo.m_ElectronicPower = electronicPower;
	m_EngineInfo.m_SteamEffectiveness = steamEffectiveness;
}

