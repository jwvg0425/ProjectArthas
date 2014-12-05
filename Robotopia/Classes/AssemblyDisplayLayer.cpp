#include "pch.h"
#include "AssemblyDisplayLayer.h"
#include "ResourceManager.h"
#include "DataManager.h"
#include "EquipmentHead.h"
#include "EquipmentEngine.h"
#include "EquipmentArmor.h"
#include "EquipmentMelee.h"
#include "EquipmentRange.h"
#include "EquipmentSteamContainer.h"
#include "EquipmentLeg.h"

bool AssemblyDisplayLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}
	m_DisplayScanBar = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_SCAN_BAR);
	m_PowerGauge = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_POWER_DEFAULT);
	
	setUIProperties(m_DisplayScanBar, cocos2d::Point(0.5, 0.5), cocos2d::Point(1055, 200), 1.0f, false, 2);
	setUIProperties(m_PowerGauge, cocos2d::Point(0, 0), cocos2d::Point(), 1.0f, true, 3);

	this->addChild(m_PowerGauge);
	this->addChild(m_DisplayScanBar);
	return true;
}

void AssemblyDisplayLayer::update(float dTime)
{
	if (m_DisplayScanBar->getNumberOfRunningActions() == 0)
	{
		m_DisplayScanBar->setVisible(false);
		m_DisplayScanBar->setPosition(cocos2d::Point(1055, 200));
	}
}

void AssemblyDisplayLayer::moveScanBar()
{
	m_DisplayScanBar->setPosition(cocos2d::Point(1055, 200));
	m_DisplayScanBar->setVisible(true);
	auto moveAction = cocos2d::MoveTo::create(1.0f, cocos2d::Point(1055, 650));
	m_DisplayScanBar->runAction(moveAction);
}

bool AssemblyDisplayLayer::getMomoryOver()
{
	return m_MemoryOver;
}

bool AssemblyDisplayLayer::getPowerOver()
{
	return m_PowerOver;
}

void AssemblyDisplayLayer::powerOverCheck()
{
	if (m_ConfirmSet.m_Engine == EL_START)
	{
		m_PowerGauge->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_POWER_OVER)->getTexture());
	}
	else
	{
		m_MaxPower = static_cast<const EngineInfo*>(GET_DATA_MANAGER()->getEquipmentInfo(EMT_ENGINE, static_cast<int>(m_ConfirmSet.m_Engine)))->m_ElectronicPower;
		int powerSum = GET_DATA_MANAGER()->getEquipmentInfo(EMT_HEAD, static_cast<int>(m_ConfirmSet.m_Head))->m_KWatt
			+ GET_DATA_MANAGER()->getEquipmentInfo(EMT_ENGINE, static_cast<int>(m_ConfirmSet.m_Armor))->m_KWatt
			+ GET_DATA_MANAGER()->getEquipmentInfo(EMT_ARMOR, static_cast<int>(m_ConfirmSet.m_Armor))->m_KWatt
			+ GET_DATA_MANAGER()->getEquipmentInfo(EMT_MELEE, static_cast<int>(m_ConfirmSet.m_Melee))->m_KWatt
			+ GET_DATA_MANAGER()->getEquipmentInfo(EMT_RANGE, static_cast<int>(m_ConfirmSet.m_Range))->m_KWatt
			+ GET_DATA_MANAGER()->getEquipmentInfo(EMT_STEAMCONTAINER, static_cast<int>(m_ConfirmSet.m_Steam))->m_KWatt
			+ GET_DATA_MANAGER()->getEquipmentInfo(EMT_LEG, static_cast<int>(m_ConfirmSet.m_Leg))->m_KWatt;

		if (powerSum > m_MaxPower)
		{
			m_PowerOver = true;
		}
		else
		{
			m_PowerOver = false;
		}
	}
}

void AssemblyDisplayLayer::memoryOverCheck()
{
	int memorySum = 0;

	if (memorySum > m_MaxMemory)
	{

	}
}
