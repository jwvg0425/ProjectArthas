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
	m_Head = GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE);
	m_Engine = GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE);
	m_Armor = GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE);
	m_Melee = GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE);
	m_Range = GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE);
	m_Steam = GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE);
	m_Leg = GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE);
	m_DisplayScanBar = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_SCAN_BAR);
//	m_PowerGauge = GET_RESOURCE_MANAGER()->createSprite(ST_ASSEMBLY_POWER_DEFAULT);
	
	setUIProperties(m_Head, cocos2d::Point(0.5, 0.5), cocos2d::Point(225, 415), 1.0f, true, 9);
	setUIProperties(m_Engine, cocos2d::Point(0.5, 0.5), cocos2d::Point(225, 415), 1.0f, true, 7);
	setUIProperties(m_Armor, cocos2d::Point(0.5, 0.5), cocos2d::Point(225, 415), 1.0f, true, 8);
	setUIProperties(m_Melee, cocos2d::Point(0.5, 0.5), cocos2d::Point(225, 415), 1.0f, true, 4);
	setUIProperties(m_Range, cocos2d::Point(0.5, 0.5), cocos2d::Point(225, 415), 1.0f, true, 4);
	setUIProperties(m_Steam, cocos2d::Point(0.5, 0.5), cocos2d::Point(225, 415), 1.0f, true, 1);
	setUIProperties(m_Leg, cocos2d::Point(0.5, 0.5), cocos2d::Point(225, 415), 1.0f, true, 2);
	setUIProperties(m_DisplayScanBar, cocos2d::Point(0.5, 0.5), cocos2d::Point(225, 200), 1.0f, false, 10);
//	setUIProperties(m_PowerGauge, cocos2d::Point(0, 0.5), cocos2d::Point(75, 130), 1.0f, true, 10);

	this->addChild(m_Steam);
	this->addChild(m_Leg);
	this->addChild(m_Melee);
	this->addChild(m_Range);
	this->addChild(m_Engine);
	this->addChild(m_Armor);
	this->addChild(m_Head);
//	this->addChild(m_PowerGauge);
	this->addChild(m_DisplayScanBar);
	return true;
}

void AssemblyDisplayLayer::assembleRobot()
{
	if (m_PrevConfirmSet.m_Head != m_ConfirmSet.m_Head)
	{
		if (m_ConfirmSet.m_Head == HL_START)
		{
			m_Head->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE)->getTexture());
		}
		else
		{
			m_Head->setTexture(GET_RESOURCE_MANAGER()->createSprite(GET_DATA_MANAGER()->getEquipmentInfo(EMT_HEAD, m_ConfirmSet.m_Head)->m_FrontSprite)->getTexture());
		}
	}
	else if (m_PrevConfirmSet.m_Engine != m_ConfirmSet.m_Engine)
	{
		if (m_ConfirmSet.m_Engine == EL_START)
		{
			m_Engine->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE)->getTexture());
		}
		else
		{
			m_Engine->setTexture(GET_RESOURCE_MANAGER()->createSprite(GET_DATA_MANAGER()->getEquipmentInfo(EMT_ENGINE, m_ConfirmSet.m_Engine)->m_FrontSprite)->getTexture());
		}
	}
	else if (m_PrevConfirmSet.m_Armor != m_ConfirmSet.m_Armor)
	{
		if (m_ConfirmSet.m_Armor == AL_START)
		{
			m_Armor->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE)->getTexture());
		}
		else
		{
			m_Armor->setTexture(GET_RESOURCE_MANAGER()->createSprite(GET_DATA_MANAGER()->getEquipmentInfo(EMT_ARMOR, m_ConfirmSet.m_Armor)->m_FrontSprite)->getTexture());
		}
	}
	else if (m_PrevConfirmSet.m_Melee != m_ConfirmSet.m_Melee)
	{
		if (m_ConfirmSet.m_Melee == ML_START)
		{
			m_Melee->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE)->getTexture());
		}
		else
		{
			m_Melee->setTexture(GET_RESOURCE_MANAGER()->createSprite(GET_DATA_MANAGER()->getEquipmentInfo(EMT_MELEE, m_ConfirmSet.m_Melee)->m_FrontSprite)->getTexture());
		}
	}
	else if (m_PrevConfirmSet.m_Range != m_ConfirmSet.m_Range)
	{
		if (m_ConfirmSet.m_Range == RL_START)
		{
			m_Range->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE)->getTexture());
		}
		else
		{
			m_Range->setTexture(GET_RESOURCE_MANAGER()->createSprite(GET_DATA_MANAGER()->getEquipmentInfo(EMT_RANGE, m_ConfirmSet.m_Range)->m_FrontSprite)->getTexture());
		}
	}
	else if (m_PrevConfirmSet.m_Steam != m_ConfirmSet.m_Steam)
	{
		if (m_ConfirmSet.m_Steam == SCL_START)
		{
			m_Steam->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE)->getTexture());
		}
		else
		{
			m_Steam->setTexture(GET_RESOURCE_MANAGER()->createSprite(GET_DATA_MANAGER()->getEquipmentInfo(EMT_STEAMCONTAINER, m_ConfirmSet.m_Steam)->m_FrontSprite)->getTexture());
		}
	}
	else if (m_PrevConfirmSet.m_Leg != m_ConfirmSet.m_Leg)
	{
		if (m_ConfirmSet.m_Leg == LL_START)
		{
			m_Leg->setTexture(GET_RESOURCE_MANAGER()->createSprite(ST_FRONT_NONE)->getTexture());
		}
		else
		{
			m_Leg->setTexture(GET_RESOURCE_MANAGER()->createSprite(GET_DATA_MANAGER()->getEquipmentInfo(EMT_LEG, m_ConfirmSet.m_Leg)->m_FrontSprite)->getTexture());
		}
	}

	m_PrevConfirmSet = m_ConfirmSet;
}

void AssemblyDisplayLayer::update(float dTime)
{
	if (m_DisplayScanBar->getNumberOfRunningActions() == 0 || m_DisplayScanBar->getPosition().y > 638)
	{
		m_DisplayScanBar->setVisible(false);
		m_DisplayScanBar->setPosition(cocos2d::Point(225, 200));
	}
}

void AssemblyDisplayLayer::moveScanBar()
{
	m_DisplayScanBar->setPosition(cocos2d::Point(225, 200));
	m_DisplayScanBar->setVisible(true);
	auto moveAction = cocos2d::MoveTo::create(1.0f, cocos2d::Point(225, 640));
	m_DisplayScanBar->runAction(moveAction);
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

//Skill 만들고 구현하기
void AssemblyDisplayLayer::memoryOverCheck()
{
	int memorySum = 0;

	if (memorySum > m_MaxMemory)
	{

	}
}

bool AssemblyDisplayLayer::getMomoryOver()
{
	return m_MemoryOver;
}

bool AssemblyDisplayLayer::getPowerOver()
{
	return m_PowerOver;
}

void AssemblyDisplayLayer::setConfirmSet(ConfirmSet confirmSet)
{
	m_ConfirmSet = confirmSet;
}
