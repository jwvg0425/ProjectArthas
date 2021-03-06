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
								  int upgradePrice, bool isLock, float attackDamage, float attackSpeed,
								  SpriteType front, SpriteType outLine, SpriteType icon)
{
	m_MeleeInfo.m_EquipmentType = equipmentType;
	m_MeleeInfo.m_Type = meleeType;
	m_MeleeInfo.m_Level = level;
	m_MeleeInfo.m_KWatt = kWatt;
	m_MeleeInfo.m_UpgradePrice = upgradePrice;
	m_MeleeInfo.m_IsLock = isLock;
	m_MeleeInfo.m_AttackDamage = attackDamage;
	m_MeleeInfo.m_AttackSpeed = attackSpeed;
	m_MeleeInfo.m_FrontSprite = front;
	m_MeleeInfo.m_FrontOutline = outLine;
	m_MeleeInfo.m_IconSprite = icon;

	if (m_MeleeInfo.m_IsLock)
	{
		m_Icon->changeIconState(ICON_LOCKED);
	}
	else
	{
		m_Icon->changeIconState(ICON_DEFAULT);
	}
}

void EquipmentMelee::setEquipment(MeleeInfo meleeInfo)
{
	setEquipment(meleeInfo.m_EquipmentType, static_cast<MeleeList>(meleeInfo.m_Type),
				 meleeInfo.m_Level, meleeInfo.m_KWatt,
				 meleeInfo.m_UpgradePrice, meleeInfo.m_IsLock,
				 meleeInfo.m_AttackDamage, meleeInfo.m_AttackSpeed,
				 meleeInfo.m_FrontSprite, meleeInfo.m_FrontOutline, meleeInfo.m_IconSprite);
	setEquipmentSprite(meleeInfo.m_FrontSprite, meleeInfo.m_FrontOutline, meleeInfo.m_IconSprite);
}

MeleeInfo EquipmentMelee::getEquipmentInfo()
{
	return m_MeleeInfo;
}


MeleeInfo* MeleeInfo::clone()
{
	return new MeleeInfo(*this);
}

MeleeInfo::MeleeInfo()
{

}

MeleeInfo::MeleeInfo(const MeleeInfo& other) : EquipmentInfo(other)
{
	m_AttackDamage = other.m_AttackDamage;
	m_AttackSpeed = other.m_AttackSpeed;
}
