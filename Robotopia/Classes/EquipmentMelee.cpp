#include "pch.h"
#include "EquipmentMelee.h"
#include "IconLayer.h"

bool EquipmentMelee::init()
{
	if (!EquipmentAbstract::init())
	{
		return false;
	}
	m_Icon = IconLayer::create();
	this->addChild(m_Icon);
	return true;
}

void EquipmentMelee::update(float dTime)
{
	if (m_Icon != nullptr)
	{
		m_Icon->update(dTime);
	}
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
	if (m_MeleeInfo.m_IsLock)
	{
		m_Icon->changeIconState(ICON_LOCKED);
	}
}

void EquipmentMelee::setEquipment(MeleeInfo meleeInfo)
{
	setEquipment(meleeInfo.m_EquipmentType, meleeInfo.m_MeleeType,
				 meleeInfo.m_Level, meleeInfo.m_KWatt,
				 meleeInfo.m_UpgradePrice, meleeInfo.m_IsLock,
				 meleeInfo.m_AttackDamage, meleeInfo.m_AttackSpeed);
}

EquipmentMelee::MeleeInfo EquipmentMelee::getEquipmentInfo()
{
	return m_MeleeInfo;
}

