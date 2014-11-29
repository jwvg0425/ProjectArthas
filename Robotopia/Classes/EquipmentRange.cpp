#include "pch.h"
#include "EquipmentRange.h"
#include "IconLayer.h"

bool EquipmentRange::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}
	m_Icon = nullptr;

	return true;
}

void EquipmentRange::update(float dTime)
{
	if (m_Icon != nullptr)
	{
		m_Icon->update(dTime);
	}
}

void EquipmentRange::enter()
{
}

void EquipmentRange::exit()
{
}

bool EquipmentRange::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentRange::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

void EquipmentRange::setEquipment(EquipmentType equipmentType, RangeList rangeType, int level, int kWatt, int upgradePrice, 
								  bool isLock, float attackDamage, float attackSpeed, float attackRange)
{
	m_RangeInfo.m_EquipmentType = equipmentType;
	m_RangeInfo.m_RangeType = rangeType;
	m_RangeInfo.m_Level = level;
	m_RangeInfo.m_KWatt = kWatt;
	m_RangeInfo.m_UpgradePrice = upgradePrice;
	m_RangeInfo.m_IsLock = isLock;
	m_RangeInfo.m_AttackDamage = attackDamage;
	m_RangeInfo.m_AttackSpeed = attackSpeed;
	m_RangeInfo.m_AttackRange = attackRange;
}

EquipmentRange::RangeInfo EquipmentRange::getEquipmentInfo()
{
	return m_RangeInfo;
}

