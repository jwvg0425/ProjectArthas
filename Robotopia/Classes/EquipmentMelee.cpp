#include "pch.h"
#include "EquipmentMelee.h"

bool EquipmentMelee::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}

	return true;
}

void EquipmentMelee::update(float dTime)
{
}

void EquipmentMelee::enter()
{
}

void EquipmentMelee::exit()
{
}

bool EquipmentMelee::onContactBegin(cocos2d::PhysicsContact& contact)
{
	return true;
}

void EquipmentMelee::onContactSeparate(cocos2d::PhysicsContact& contact)
{
}

void EquipmentMelee::setEquipment(EquipmentType equipmentType, MeleeList meleeType, int level, int kWatt, 
								  int upgradePrice, bool isLock, float attackDamage, float attackSpeed)
{
	m_MeleeInfo.m_EquipmentType = equipmentType;
	m_MeleeInfo.m_MeleeType = meleeType;
	m_MeleeInfo.m_Level = level;
	m_MeleeInfo.m_KWatt = kWatt;
	m_MeleeInfo.m_UpgradePrice = upgradePrice;
	m_MeleeInfo.m_IsLock = isLock;
	m_MeleeInfo.m_AttackDamage = attackDamage;
	m_MeleeInfo.m_AttackSpeed = attackSpeed;
}

